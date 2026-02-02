#include <processing/image_manipulation.h>
#include <iostream>

//-------------------------------------------------------------------------------------------------//

std::unique_ptr<ImageData> ImageManipulation::createMaskedImage(const ImageData &in, const ImageData &mask)
{
    if (in.width != mask.width || in.height != mask.height || in.channels != mask.channels)
    {
        return nullptr;
    }

    std::unique_ptr<ImageData> p_output{ std::make_unique<ImageData>(in.width, in.height, in.channels) };

    for (int y = 0; y < in.height; y++)
    {
        for (int x = 0; x < in.width; x++)
        {
            if (x < mask.width && y < mask.height)
            {
                int pixelOffset{ (y * in.width + x) * in.channels };
                uint8_t *p_maskPixelAlpha{ mask.p_data + pixelOffset + 3 };
                if (*p_maskPixelAlpha != 0)
                {
                    std::memcpy(p_output->p_data + pixelOffset, in.p_data + pixelOffset, (size_t)in.channels);
                }
            }
        }
    }

    return std::move(p_output);
}

//-------------------------------------------------------------------------------------------------//

std::unique_ptr<ImageData> ImageManipulation::blendInputsWithTemplate(const std::vector<ColourMappedImageData> &inputs,
                                                                      ImageData &temp)
{
    if (inputs.empty())
    {
        return nullptr;
    }

    // Verify that all sizes are correct
    int inWidth{ inputs[0].p_imageData->width };
    int tempWidth{ temp.width };
    int height{ inputs[0].p_imageData->height };
    for (const auto &input : inputs)
    {
        if (input.p_imageData->width != inWidth || input.p_imageData->height != height)
        {
            return nullptr;
        }
    }

    if (temp.width != tempWidth || temp.height != height)
    {
        return nullptr;
    }

    std::unique_ptr<ImageData> p_output{ std::make_unique<ImageData>(temp.width, temp.height, temp.channels) };

    int numTiles{ temp.width / inWidth };
    for (int t = 0; t < numTiles; t++)
    {
        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < inWidth; x++)
            {
                int inputOffsetBytes{ (y * inWidth + x) * temp.channels };
                int outputOffsetBytes{ (y * temp.width + x + (t * inWidth)) * temp.channels };

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
                                (size_t)p_output->channels);
                }
            }
        }
    }

    return std::move(p_output);
}

//-------------------------------------------------------------------------------------------------//

std::unique_ptr<ImageData> ImageManipulation::applyNoise(const ImageData &in, const Noise &noise, float opacity)
{
    std::unique_ptr<ImageData> p_output{ std::make_unique<ImageData>(in.width, in.height, in.channels) };

    for (int y = 0; y < in.height; y++)
    {
        for (int x = 0; x < in.width; x++)
        {
            int offsetBytes{ (y * in.width + x) * in.channels };

            float normalizedNoise{ noise.get2D(x, y) / 2.f + 0.5f };
            uint8_t scaledNoise{ (uint8_t)(normalizedNoise * 255.f) };
            uint8_t a{ *(in.p_data + offsetBytes + 3) };
            if (a != 0)
            {
                uint8_t r{ *(in.p_data + offsetBytes) };
                uint8_t g{ *(in.p_data + offsetBytes + 1) };
                uint8_t b{ *(in.p_data + offsetBytes + 2) };

                *(p_output->p_data + offsetBytes) = (uint8_t)std::lerp(r, scaledNoise, opacity);
                *(p_output->p_data + offsetBytes + 1) = (uint8_t)std::lerp(g, scaledNoise, opacity);
                *(p_output->p_data + offsetBytes + 2) = (uint8_t)std::lerp(b, scaledNoise, opacity);
                *(p_output->p_data + offsetBytes + 3) = (uint8_t)std::lerp(a, scaledNoise, opacity);
            }
        }
    }

    return std::move(p_output);
}

//-------------------------------------------------------------------------------------------------//
