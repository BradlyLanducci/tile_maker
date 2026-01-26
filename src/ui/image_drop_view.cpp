#include <ui/image_drop_view.h>

//-------------------------------------------------------------------------------------------------//

constexpr int TEXT_SIZE{ 25 };

//-------------------------------------------------------------------------------------------------//

ImageDropView::ImageDropView(const juce::String &title)
    : m_title(title)
{
    addAndMakeVisible(m_handler);
}

//-------------------------------------------------------------------------------------------------//

void ImageDropView::paint(juce::Graphics &g)
{
    g.fillAll(juce::Colours::beige);
    auto bounds{ getBounds() };
    g.drawText(m_title, 0, 0, bounds.getWidth(), TEXT_SIZE, juce::Justification::centred);
}

//-------------------------------------------------------------------------------------------------//

void ImageDropView::resized()
{
    auto bounds{ getBounds() };
    bounds = bounds.removeFromBottom(bounds.getHeight() - TEXT_SIZE);
    const int padding{ 4 };
    bounds.reduce(padding, padding);
    m_handler.setBounds(padding, TEXT_SIZE + padding, bounds.getWidth(), bounds.getHeight());
}

//-------------------------------------------------------------------------------------------------//
