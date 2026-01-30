#pragma once

#include <processing/image_data.h>
#include <processing/noise.h>

//-------------------------------------------------------------------------------------------------//

class ImageManipulation
{
public:
    /// @brief Applies a mask image to an input image
    /// @param in The input image to modify
    /// @param mask The mask to apply to the input
    static std::unique_ptr<ImageData> createMaskedImage(const ImageData &in, const ImageData &mask);

    /// @brief Creates all path variants from provided input and path textures
    /// @param inputs Vector of colours mapped to image data
    /// @param tmp Template texture
    static std::unique_ptr<ImageData> blendInputsWithTemplate(const std::vector<ColourMappedImageData> &inputs,
                                                              ImageData &temp);

    static std::unique_ptr<ImageData> applyNoise(const ImageData &in, const Noise &noise, float opacity);
};

//-------------------------------------------------------------------------------------------------//
