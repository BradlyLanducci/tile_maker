#include <ui/image_handler.h>
#include <ui/image_frame.h>
#include <ui/image_list.h>

//-------------------------------------------------------------------------------------------------//

void ImageHandler::paint(juce::Graphics &g)
{
    g.fillAll(juce::Colours::beige);
}

//-------------------------------------------------------------------------------------------------//

bool ImageHandler::isInterestedInFileDrag(const juce::StringArray &files)
{
    for (const auto &file : files)
    {
        if (!isValidType(file))
        {
            return false;
        }
    }
    return true;
}

//-------------------------------------------------------------------------------------------------//

void ImageHandler::filesDropped(const juce::StringArray &files, int x, int y)
{
    (void)x;
    (void)y;

    auto bounds{ getBounds() };

    if (files.size() == 1)
    {
        mp_imageDisplayer = std::make_unique<ImageFrame>(files[0]);
    }
    else
    {
        mp_imageDisplayer = std::make_unique<ImageList>(files);
    }
    mp_imageDisplayer->setBounds(0, 0, bounds.getWidth(), bounds.getHeight());
    addAndMakeVisible(mp_imageDisplayer.get());
}

//-------------------------------------------------------------------------------------------------//

bool ImageHandler::isValidType(juce::String file)
{
    for (const auto &validType : m_validTypes)
    {
        if (file.contains(validType))
        {
            return true;
        }
    }
    return false;
}

//-------------------------------------------------------------------------------------------------//
