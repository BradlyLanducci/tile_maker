#include <ui/image_drop_view.h>
#include <ui/image_frame.h>
#include <ui/image_list_container.h>

#include <image/image_manipulation.h>

//-------------------------------------------------------------------------------------------------//

const float HOVER_ALPHA{ 0.75f };

//-------------------------------------------------------------------------------------------------//

ImageDropView::ImageDropView(std::function<void()> imageUpdatedCb)
    : m_imageUpdatedCb(imageUpdatedCb)
{
}

//-------------------------------------------------------------------------------------------------//

void ImageDropView::paint(juce::Graphics &g)
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

        g.drawText("Drag image here", getLocalBounds(), juce::Justification::centred);
    }
}

//-------------------------------------------------------------------------------------------------//

void ImageDropView::fileDragEnter(const juce::StringArray &, int, int)
{
    m_hovered = true;
    repaint();
}

//-------------------------------------------------------------------------------------------------//

void ImageDropView::fileDragExit(const juce::StringArray &)
{
    m_hovered = false;
    repaint();
}

//-------------------------------------------------------------------------------------------------//

juce::StringArray ImageDropView::getImages()
{
    return m_images;
}

//-------------------------------------------------------------------------------------------------//

bool ImageDropView::isInterestedInFileDrag(const juce::StringArray &files)
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

void ImageDropView::filesDropped(const juce::StringArray &files, int x, int y)
{
    (void)x;
    (void)y;

    m_hovered = false;
    m_images = files;

    auto bounds{ getBounds() };

    if (files.size() == 1)
    {
        std::unique_ptr<ImageData> imageData{ std::make_unique<ImageData>(files[0].toStdString()) };
        mp_imageDisplayer = std::make_unique<ImageFrame>(std::move(imageData));
    }
    else
    {
        mp_imageDisplayer = std::make_unique<ImageListContainer>(files);
    }

    mp_imageDisplayer->setBounds(0, 0, bounds.getWidth(), bounds.getHeight());
    addAndMakeVisible(mp_imageDisplayer.get());

    m_imageUpdatedCb();
}

//-------------------------------------------------------------------------------------------------//

bool ImageDropView::isValidType(juce::String file)
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
