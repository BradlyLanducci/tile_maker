#include <ui/image_handler.h>
#include <ui/image_frame.h>
#include <ui/image_list_container.h>

//-------------------------------------------------------------------------------------------------//

const float HOVER_ALPHA{ 0.75f };

//-------------------------------------------------------------------------------------------------//

void ImageHandler::paint(juce::Graphics &g)
{
    if (mp_imageDisplayer)
    {
        if (m_hovered)
        {
            mp_imageDisplayer->setAlpha(HOVER_ALPHA);
        }
        else
        {
            mp_imageDisplayer->setAlpha(1.f);
        }
    }
    else
    {
        if (m_hovered)
        {
            g.fillAll(juce::Colours::red.withAlpha(HOVER_ALPHA));
        }
        else
        {
            g.fillAll(juce::Colours::red);
        }

        g.drawText("Drag file here", getLocalBounds(), juce::Justification::centred);
    }
}

//-------------------------------------------------------------------------------------------------//

void ImageHandler::fileDragEnter(const juce::StringArray &, int, int)
{
    m_hovered = true;
    repaint();
}

//-------------------------------------------------------------------------------------------------//

void ImageHandler::fileDragExit(const juce::StringArray &)
{
    m_hovered = false;
    repaint();
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

    m_hovered = false;

    auto bounds{ getBounds() };

    if (files.size() == 1)
    {
        mp_imageDisplayer = std::make_unique<ImageFrame>(files[0]);
    }
    else
    {
        mp_imageDisplayer = std::make_unique<ImageListContainer>(files);
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
