#include <processing/image_data.h>

//-------------------------------------------------------------------------------------------------//

class ImageManipulation
{
public:
    /// @brief Applies a mask image to an input image
    /// @param in The input image to modify
    /// @param mask The mask to apply to the input
    static std::unique_ptr<ImageData> createMaskedImage(const ImageData &in, const ImageData &mask);

    /// @brief Creates all path variants from provided input and path textures
    /// @param ground Ground texture
    /// @param path Path texture
    /// @param maskSheet The spritesheet of masks
    static void createPathFromSpriteSheet(const ImageData &ground, const ImageData &path, const ImageData &maskSheet);
};

//-------------------------------------------------------------------------------------------------//
