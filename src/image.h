#pragma once

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include <stb_image.h>
#include <stb_image_write.h>

#include <cstdint>
#include <filesystem>
#include <iostream>
#include <string>

constexpr uint32_t DESIRED_CHANNELS{ 4 };
const std::string INPUT_DIR{ "input" };
const std::string OUTPUT_DIR{ "output" };
const std::string TEMPLATE_DIR{ "templates" };

struct Image
{
    Image(std::filesystem::path path)
        : data(stbi_load(path.string().c_str(), &width, &height, &channels, DESIRED_CHANNELS))
    {
        path.replace_extension();
        filename = path.filename().string();
    }

    ~Image()
    {
        if (data)
        {
            stbi_image_free(data);
        }
    }

    int width{};
    int height{};
    int channels{};
    uint8_t *data{ nullptr };
    std::string filename{};

    static void createMaskedImage(const Image &in, const Image &mask)
    {
        if (in.filename == ".gitkeep" || mask.filename == ".gitkeep")
        {
            return;
        }

        for (uint32_t y = 0; y < in.height; y++)
        {
            for (uint32_t x = 0; x < in.width; x++)
            {
                if (x < mask.width && y < mask.height)
                {
                    uint32_t pixelOffset{ (y * in.width + x) * in.channels };
                    uint8_t *inPixelAlpha{ in.data + pixelOffset + 3 };
                    uint8_t *maskPixelAlpha{ mask.data + pixelOffset + 3 };
                    if (*maskPixelAlpha == 0)
                    {
                        *inPixelAlpha = 0;
                    }
                }
            }
        }

        if (!stbi_write_png((OUTPUT_DIR + "/" + in.filename + "_" + mask.filename + ".png").c_str(), in.width,
                            in.height, in.channels, in.data, in.width * in.channels))
        {
            std::cerr << "Failed to write\n";
        }
    }
};