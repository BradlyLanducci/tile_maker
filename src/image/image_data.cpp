#include <image/image_data.h>

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include <stb_image.h>
#include <stb_image_write.h>

//-------------------------------------------------------------------------------------------------//

ImageData::ImageData(int imageWidth, int imageHeight, int imageChannels)
    : width(imageWidth)
    , height(imageHeight)
    , channels(imageChannels)
    , data((uint8_t *)malloc(width * height * imageChannels)) // We malloc to be consistent with stbi
{
    std::fill(data, data + getSizeBytes(), 0);
}

//-------------------------------------------------------------------------------------------------//

ImageData::ImageData(std::filesystem::path path)
    : data(stbi_load(path.string().c_str(), &width, &height, &channels, DESIRED_CHANNELS))
{
    path.replace_extension();
    filename = path.filename().string();
}

//-------------------------------------------------------------------------------------------------//

ImageData::~ImageData()
{
    if (data)
    {
        free(data);
        data = nullptr;
    }
}

//-------------------------------------------------------------------------------------------------//

uint32_t ImageData::getSizeBytes()
{
    return width * height * channels;
}

//-------------------------------------------------------------------------------------------------//
