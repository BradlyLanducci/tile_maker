#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include <stb_image.h>
#include <stb_image_write.h>

#include <cstdint>
#include <filesystem>
#include <iostream>
#include <string>

constexpr uint32_t DESIRED_CHANNELS{ 4 };
const std::string TEMPLATE_DIR{ "templates" };
const std::string INPUT_DIR{ "input" };
const std::string OUTPUT_DIR{ "output" };

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

void createMaskedImage(const Image &in, const Image &mask)
{
    for (uint32_t y = 0; y < in.height; y++)
    {
        for (uint32_t x = 0; x < in.width; x++)
        {
            if (x < mask.width && y < mask.height)
            {
                uint32_t pixelOffset{ (y * in.width + x) * in.channels };
                uint8_t *inPixel{ in.data + pixelOffset };
                uint8_t *maskPixel{ mask.data + pixelOffset };
                if (maskPixel[3] == 0)
                {
                    inPixel[3] = 0;
                }
            }
        }
    }

    if (!stbi_write_png((OUTPUT_DIR + "/" + in.filename + "_" + mask.filename + ".png").c_str(), in.width, in.height,
                        in.channels, in.data, in.width * in.channels))
    {
        std::cerr << "Failed to write\n";
    }
}

int main()
{
    for (const auto &inFile : std::filesystem::directory_iterator{ INPUT_DIR })
    {
        Image inputImage{ inFile.path() };
        std::string inFilename{ inFile.path().filename().string() };

        for (const auto &templateFile : std::filesystem::directory_iterator{ TEMPLATE_DIR })
        {
            Image templateImage{ templateFile.path() };
            createMaskedImage(inputImage, templateImage);
        }
    }

    return 0;
}
