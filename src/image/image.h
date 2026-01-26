#pragma once

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include <stb_image.h>
#include <stb_image_write.h>

#include <cstdint>
#include <filesystem>
#include <string>

//-------------------------------------------------------------------------------------------------//

constexpr uint32_t DESIRED_CHANNELS{ 4 };
const std::string INPUT_DIR{ "input" };
const std::string OUTPUT_DIR{ "output" };
const std::string TEMPLATE_DIR{ "templates" };

//-------------------------------------------------------------------------------------------------//

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
};

//-------------------------------------------------------------------------------------------------//
