#pragma once

#include <cstdint>
#include <filesystem>
#include <string>

//-------------------------------------------------------------------------------------------------//

constexpr uint32_t DESIRED_CHANNELS{ 4 };
const std::string INPUT_DIR{ "input" };
const std::string OUTPUT_DIR{ "output" };
const std::string TEMPLATE_DIR{ "templates" };

//-------------------------------------------------------------------------------------------------//

struct ImageData
{
    ImageData(int imageWidth, int imageHeight, int imageChannels);
    ImageData(std::filesystem::path path);
    ~ImageData();

    uint32_t getSizeBytes();

    int width{};
    int height{};
    int channels{};
    uint8_t *p_data{ nullptr };
    std::string filename{};
};

//-------------------------------------------------------------------------------------------------//
