#include <processing/image_data.h>

#include <stb.h>

//-------------------------------------------------------------------------------------------------//

constexpr uint32_t DESIRED_CHANNELS{ 4 };

//-------------------------------------------------------------------------------------------------//

ImageData::ImageData(int imageWidth, int imageHeight, int imageChannels)
    : width(imageWidth)
    , height(imageHeight)
    , channels(imageChannels)
    , p_data((uint8_t *)malloc((size_t)(width * height * imageChannels))) // We malloc to be consistent with stbi
{
    std::fill(p_data, p_data + getSizeBytes(), 0);
}

//-------------------------------------------------------------------------------------------------//

ImageData::ImageData(std::filesystem::path path)
    : p_data(stbi_load(path.string().c_str(), &width, &height, &channels, DESIRED_CHANNELS))
    , filepath(path.parent_path().string())
{
    path.replace_extension();
    filename = path.filename().string();
}

//-------------------------------------------------------------------------------------------------//

ImageData::~ImageData()
{
    if (p_data)
    {
        free(p_data);
        p_data = nullptr;
    }
}

//-------------------------------------------------------------------------------------------------//

uint32_t ImageData::getSizeBytes() const
{
    return (uint32_t)(width * height * channels);
}

//-------------------------------------------------------------------------------------------------//

void ImageData::writeToDisk()
{
    if (!std::filesystem::exists(filepath))
    {
        std::filesystem::create_directory(filepath);
    }

    if (!stbi_write_png((filepath + filename + ".png").c_str(), width, height, channels, p_data, width * channels))
    {
        std::cerr << "Failed to write" << std::endl;
    }
}

//-------------------------------------------------------------------------------------------------//
