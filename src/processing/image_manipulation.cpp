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

std::unique_ptr<ImageData> ImageManipulation::blendInputsFromTemplate(const std::vector<ColourMappedImageData> &inputs,
                                                                      const std::vector<ImageData> &templates)
{
    if (inputs.empty() || templates.empty())
    {
        return nullptr;
    }

    // Verify that all sizes are correct
    uint32_t inWidth{ (uint32_t)inputs[0].p_imageData->width };
    uint32_t tempWidth{ (uint32_t)templates[0].width };
    uint32_t height{ (uint32_t)inputs[0].p_imageData->height };
    for (const auto &input : inputs)
    {
        if (input.p_imageData->width != inWidth || input.p_imageData->height != height)
        {
            return nullptr;
        }
    }

    for (const auto &temp : templates)
    {
        if (temp.width != tempWidth || temp.height != height)
        {
            return nullptr;
        }
    }

    std::unique_ptr<ImageData> p_output{ std::make_unique<ImageData>(templates[0].width, templates[0].height,
                                                                     templates[0].channels) };

    for (const auto &temp : templates)
    {
        uint32_t numTiles{ templates[0].width / inWidth };
        for (uint32_t t = 0; t < numTiles; t++)
        {
            for (uint32_t y = 0; y < height; y++)
            {
                for (uint32_t x = 0; x < inWidth; x++)
                {
                    uint32_t inputOffsetBytes{ (y * inWidth + x) * temp.channels };
                    uint32_t outputOffsetBytes{ (y * temp.width + x + (t * inWidth)) * temp.channels };

                    uint8_t r{ *(temp.p_data + outputOffsetBytes) };
                    uint8_t g{ *(temp.p_data + outputOffsetBytes + 1) };
                    uint8_t b{ *(temp.p_data + outputOffsetBytes + 2) };

                    uint8_t *tileDataToUse{ nullptr };
                    for (const auto &input : inputs)
                    {
                        if (input.colour == juce::Colour(r, g, b))
                        {
                            tileDataToUse = input.p_imageData->p_data;
                            break;
                        }
                    }

                    if (tileDataToUse && outputOffsetBytes < (p_output->width * p_output->height * p_output->channels))
                    {
                        std::memcpy(p_output->p_data + outputOffsetBytes, tileDataToUse + inputOffsetBytes,
                                    p_output->channels);
                    }
                }
            }
        }
    }

    return std::move(p_output);
}

//-------------------------------------------------------------------------------------------------//
