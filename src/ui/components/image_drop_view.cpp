#include <ui/components/image_drop_view.h>
#include <ui/components/image_frame.h>
#include <processing/image_manipulation.h>

//-------------------------------------------------------------------------------------------------//

const float HOVER_ALPHA{ 0.75f };

//-------------------------------------------------------------------------------------------------//

ImageDropView::ImageDropView(juce::ValueTree tree, FactoryCallback factoryCb)
    : m_factoryCb(factoryCb)
    , m_tree(tree)

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

    m_tree.removeAllChildren(nullptr);

    for (const auto &file : files)
    {
        juce::Identifier id{ juce::Identifier(file) };
        juce::ValueTree subTree{ id };
        m_tree.appendChild(subTree, nullptr);
    }

    mp_imageDisplayer = m_factoryCb(this, m_tree);
    if (mp_imageDisplayer)
    {
        mp_imageDisplayer->setBounds(0, 0, bounds.getWidth(), bounds.getHeight());
        addAndMakeVisible(mp_imageDisplayer.get());
    }
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
