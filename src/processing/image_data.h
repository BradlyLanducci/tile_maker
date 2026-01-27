#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include <cstdint>
#include <filesystem>
#include <string>

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

struct ColourMappedImageData
{
    ColourMappedImageData(juce::Colour mappedColour, std::unique_ptr<ImageData> p_mappedImageData)
        : colour(mappedColour)
        , p_imageData(std::move(p_mappedImageData))
    {
    }

    juce::Colour colour;
    std::unique_ptr<ImageData> p_imageData{ nullptr };
};

//-------------------------------------------------------------------------------------------------//
