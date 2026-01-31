#include <ui/components/image_color_picker.h>
#include <juce_gui_extra/juce_gui_extra.h>
#include <ui/theme/theme.h>

//-------------------------------------------------------------------------------------------------//

ImageColorPicker::ImageColorPicker(juce::ValueTree tree)
    : m_tree(tree)
{
}

//-------------------------------------------------------------------------------------------------//

void ImageColorPicker::paint(juce::Graphics &g)
{
    auto colour{ juce::Colour::fromString(
        m_tree.getProperty(Theme::COLOUR_KEY, juce::Colours::black.toString()).toString()) };
    g.setColour(colour);
    auto bounds{ getLocalBounds().removeFromRight(50) };
    bounds.reduce(Theme::DEFAULT_PADDING, Theme::DEFAULT_PADDING);
    auto sideLength{ std::min(bounds.getWidth(), bounds.getHeight()) };
    g.fillRect(bounds.getX(), bounds.getY(), sideLength, sideLength);
}

//-------------------------------------------------------------------------------------------------//

void ImageColorPicker::mouseUp(const juce::MouseEvent &event)
{
    (void)event;
    auto colourSelector{ std::make_unique<juce::ColourSelector>() };
    colourSelector->setName("background");
    colourSelector->setCurrentColour(findColour(juce::TextButton::buttonColourId));
    colourSelector->setColour(juce::ColourSelector::backgroundColourId, juce::Colours::transparentBlack);
    colourSelector->setSize(300, 400);
    colourSelector->addChangeListener(this);
    juce::CallOutBox::launchAsynchronously(std::move(colourSelector), getScreenBounds(), nullptr);
}

//-------------------------------------------------------------------------------------------------//

void ImageColorPicker::changeListenerCallback(juce::ChangeBroadcaster *source)
{
    auto colourSelector{ static_cast<juce::ColourSelector *>(source) };
    if (colourSelector)
    {
        m_tree.setProperty(Theme::COLOUR_KEY, colourSelector->getCurrentColour().toString(), nullptr);
        repaint();
    }
}

//-------------------------------------------------------------------------------------------------//
