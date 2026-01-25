#include <image/image.h>

//-------------------------------------------------------------------------------------------------//

namespace ImageManipulation
{
    /// @brief Applies a mask image to an input image
    /// @param in The input image to modify
    /// @param mask The mask to apply to the input
    static void createMaskedImage(const Image &in, const Image &mask);

    /// @brief Creates all path variants from provided input and path textures
    /// @param ground Ground texture
    /// @param path Path texture
    /// @param maskSheet The spritesheet of masks
    static void createPathFromSpriteSheet(const Image &ground, const Image &path, const Image &maskSheet);
}

//-------------------------------------------------------------------------------------------------//
