#include <image.h>

#include <juce_gui_basics/juce_gui_basics.h>

//-------------------------------------------------------------------------------------------------//

int main(int argc, char **argv)
{
    for (const auto &inFile : std::filesystem::directory_iterator{ INPUT_DIR })
    {
        std::string inFilename{ inFile.path().filename().string() };
        Image inputImage{ inFile.path() };
        for (const auto &templateFile : std::filesystem::directory_iterator{ TEMPLATE_DIR })
        {
            Image templateImage{ templateFile.path() };

            for (const auto &inFile2 : std::filesystem::directory_iterator{ INPUT_DIR })
            {
                if (templateImage.width > inputImage.width)
                {
                    if (inFile != inFile2)
                    {
                        Image pathImage{ inFile2.path() };
                        Image::createPathFromSpriteSheet(inputImage, pathImage, templateImage);
                    }
                }
                else
                {
                    Image::createMaskedImage(inputImage, templateImage);
                }
            }
        }
    }

    return 0;
}

//-------------------------------------------------------------------------------------------------//
