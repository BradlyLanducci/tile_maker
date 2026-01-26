#include <processing/image_manipulation.h>

#include <iostream>

//-------------------------------------------------------------------------------------------------//

#define ASSERT(condition, message)                                                                                     \
    {                                                                                                                  \
        if (!(condition))                                                                                              \
        {                                                                                                              \
            std::cerr << message << std::endl;                                                                         \
        }                                                                                                              \
    }

//-------------------------------------------------------------------------------------------------//

std::unique_ptr<ImageData> ImageManipulation::createMaskedImage(const ImageData &in, const ImageData &mask)
{
    if (in.filename == ".gitkeep" || mask.filename == ".gitkeep")
    {
        return nullptr;
    }

    if (in.width != mask.width || in.height != mask.height || in.channels != mask.channels)
    {
        return nullptr;
    }

    std::unique_ptr<ImageData> p_output{ std::make_unique<ImageData>(in.width, in.height, in.channels) };

    for (uint32_t y = 0; y < in.height; y++)
    {
        for (uint32_t x = 0; x < in.width; x++)
        {
            if (x < mask.width && y < mask.height)
            {
                uint32_t pixelOffset{ (y * in.width + x) * in.channels };
                uint8_t *p_maskPixelAlpha{ mask.p_data + pixelOffset + 3 };
                if (*p_maskPixelAlpha != 0)
                {
                    std::memcpy(p_output->p_data + pixelOffset, in.p_data + pixelOffset, in.channels);
                }
            }
        }
    }

    return std::move(p_output);
}

//-------------------------------------------------------------------------------------------------//

std::unique_ptr<ImageData> ImageManipulation::blendABFromTemplate(const ImageData &aImageData,
                                                                  const ImageData &bImageData,
                                                                  const ImageData &tmpImageData)
{
    if (aImageData.filename[0] == '.' || bImageData.filename[0] == '.' || tmpImageData.filename[0] == '.')
    {
        return nullptr;
    }

    ASSERT((aImageData.channels == aImageData.channels) && (aImageData.channels == tmpImageData.channels),
           "All images must have the same amount of channels");
    ASSERT(tmpImageData.width % aImageData.width == 0, "Mask sheet must be multiple of aImageData");
    ASSERT(aImageData.width == bImageData.width, "aImageData and b images must have the same width");
    ASSERT((aImageData.channels == bImageData.channels) && (aImageData.channels == tmpImageData.channels),
           "All images must have the same height");

    std::unique_ptr<ImageData> p_output{ std::make_unique<ImageData>(tmpImageData.width, tmpImageData.height,
                                                                     tmpImageData.channels) };

    uint32_t aWidth{ (uint32_t)aImageData.width };
    uint32_t height{ (uint32_t)aImageData.height };

    uint32_t numTiles{ tmpImageData.width / aWidth };
    for (uint32_t t = 0; t < numTiles; t++)
    {
        for (uint32_t y = 0; y < height; y++)
        {
            for (uint32_t x = 0; x < aWidth; x++)
            {
                uint32_t aPixelOffsetBytes{ (y * aWidth + x) * aImageData.channels };
                uint32_t maskPixelOffset{ (y * tmpImageData.width + x + (t * aWidth)) * tmpImageData.channels };

                uint8_t r{ *(tmpImageData.p_data + maskPixelOffset) };
                uint8_t g{ *(tmpImageData.p_data + maskPixelOffset + 1) };
                uint8_t b{ *(tmpImageData.p_data + maskPixelOffset + 2) };
                bool isMask{ r == 0 && g == 0 && b == 0 };

                uint8_t *tileDataToUse{};
                if (isMask)
                {
                    tileDataToUse = aImageData.p_data;
                }
                else
                {
                    tileDataToUse = bImageData.p_data;
                }

                if (maskPixelOffset < (tmpImageData.width * tmpImageData.height * tmpImageData.channels))
                {
                    p_output->p_data[maskPixelOffset] = tileDataToUse[aPixelOffsetBytes];
                    p_output->p_data[maskPixelOffset + 1] = tileDataToUse[aPixelOffsetBytes + 1];
                    p_output->p_data[maskPixelOffset + 2] = tileDataToUse[aPixelOffsetBytes + 2];
                    p_output->p_data[maskPixelOffset + 3] = tileDataToUse[aPixelOffsetBytes + 3];
                }
            }
        }
    }
    std::string baseOutputDir{ OUTPUT_DIR + "/" + aImageData.filename + "/" };

    if (!std::filesystem::exists(baseOutputDir))
    {
        std::filesystem::create_directory(baseOutputDir);
    }

    return std::move(p_output);
}

//-------------------------------------------------------------------------------------------------//
