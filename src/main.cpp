#include <image.h>

int main()
{
    for (const auto &inFile : std::filesystem::directory_iterator{ GROUND_INPUT_DIR })
    {
        std::string inFilename{ inFile.path().filename().string() };
        Image inputImage{ inFile.path() };
        for (const auto &templateFile : std::filesystem::directory_iterator{ TEMPLATE_DIR })
        {
            Image templateImage{ templateFile.path() };
            if (templateImage.width > inputImage.width)
            {
                for (const auto &pathFile : std::filesystem::directory_iterator{ PATH_INPUT_DIR })
                {
                    Image pathImage{ pathFile.path() };
                    Image::createPathFromSpriteSheet(inputImage, pathImage, templateImage);
                }
            }
            else
            {
                Image::createMaskedImage(inputImage, templateImage);
            }
        }
    }

    return 0;
}
