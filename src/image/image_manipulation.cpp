#include <image/image_manipulation.h>

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

    std::unique_ptr<ImageData> output{ std::make_unique<ImageData>(in.width, in.height, in.channels) };

    for (uint32_t y = 0; y < in.height; y++)
    {
        for (uint32_t x = 0; x < in.width; x++)
        {
            if (x < mask.width && y < mask.height)
            {
                uint32_t pixelOffset{ (y * in.width + x) * in.channels };
                uint8_t *maskPixelAlpha{ mask.data + pixelOffset + 3 };
                if (*maskPixelAlpha != 0)
                {
                    std::memcpy(output->data + pixelOffset, in.data + pixelOffset, in.channels);
                }
            }
        }
    }

    return std::move(output);
}

//-------------------------------------------------------------------------------------------------//

void ImageManipulation::createPathFromSpriteSheet(const ImageData &ground, const ImageData &path,
                                                  const ImageData &maskSheet)
{
    if (ground.filename[0] == '.' || path.filename[0] == '.' || maskSheet.filename[0] == '.')
    {
        return;
    }

    ASSERT((ground.channels == path.channels) && (ground.channels == maskSheet.channels),
           "All images must have the same amount of channels");
    ASSERT(maskSheet.width % ground.width == 0, "Mask sheet must be multiple of ground");
    ASSERT(ground.width == path.width, "Ground and path images must have the same width");
    ASSERT((ground.channels == path.channels) && (ground.channels == maskSheet.channels),
           "All images must have the same height");

    uint32_t groundWidth{ (uint32_t)ground.width };
    uint32_t height{ (uint32_t)ground.height };

    uint32_t numTiles{ maskSheet.width / groundWidth };
    std::vector<uint8_t> outData(maskSheet.width * height * maskSheet.channels, 0);
    for (uint32_t t = 0; t < numTiles; t++)
    {
        uint32_t tileWidthBytes{ groundWidth * maskSheet.channels };
        for (uint32_t y = 0; y < height; y++)
        {
            for (uint32_t x = 0; x < groundWidth; x++)
            {
                uint32_t groundPixelOffsetBytes{ (y * groundWidth + x) * ground.channels };
                uint32_t maskPixelOffset{ (y * maskSheet.width + x + (t * groundWidth)) * maskSheet.channels };

                uint8_t r{ *(maskSheet.data + maskPixelOffset) };
                uint8_t g{ *(maskSheet.data + maskPixelOffset + 1) };
                uint8_t b{ *(maskSheet.data + maskPixelOffset + 2) };
                bool isMask{ r == 0 && g == 0 && b == 0 };

                uint8_t *tileDataToUse{};
                if (isMask)
                {
                    tileDataToUse = ground.data;
                }
                else
                {
                    tileDataToUse = path.data;
                }

                if (maskPixelOffset < (maskSheet.width * maskSheet.height * maskSheet.channels))
                {
                    outData[maskPixelOffset] = tileDataToUse[groundPixelOffsetBytes];
                    outData[maskPixelOffset + 1] = tileDataToUse[groundPixelOffsetBytes + 1];
                    outData[maskPixelOffset + 2] = tileDataToUse[groundPixelOffsetBytes + 2];
                    outData[maskPixelOffset + 3] = tileDataToUse[groundPixelOffsetBytes + 3];
                }
            }
        }
    }

    std::string baseOutputDir{ OUTPUT_DIR + "/" + ground.filename + "/" };

    if (!std::filesystem::exists(baseOutputDir))
    {
        std::filesystem::create_directory(baseOutputDir);
    }

    // if (!stbi_write_png(
    //         (baseOutputDir + ground.filename + "_" + path.filename + "_" + maskSheet.filename + "_spritesheet.png")
    //             .c_str(),
    //         maskSheet.width, maskSheet.height, maskSheet.channels, outData.data(),
    //         maskSheet.width * maskSheet.channels))
    // {
    //     std::cerr << "Failed to write" << std::endl;
    // }
}

//-------------------------------------------------------------------------------------------------//
