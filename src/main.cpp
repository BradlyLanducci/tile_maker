#include <image.h>

int main()
{
    for (const auto &inFile : std::filesystem::directory_iterator{ INPUT_DIR })
    {
        std::string inFilename{ inFile.path().filename().string() };
        Image inputImage{ inFile.path() };
        for (const auto &templateFile : std::filesystem::directory_iterator{ TEMPLATE_DIR })
        {
            Image templateImage{ templateFile.path() };
            Image::createMaskedImage(inputImage, templateImage);
        }
    }

    return 0;
}
