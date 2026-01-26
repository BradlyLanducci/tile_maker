#include <ui/components/image_color_picker.h>
#include <juce_gui_extra/juce_gui_extra.h>

//-------------------------------------------------------------------------------------------------//

ImageColorPicker::ImageColorPicker(const juce::String &imageName, juce::Colour defaultColour)
    : m_imageName(imageName)
    , m_colour(defaultColour)
{
}

//-------------------------------------------------------------------------------------------------//

void ImageColorPicker::paint(juce::Graphics &g)
{
    g.setColour(m_colour);
    auto bounds{ getLocalBounds().removeFromRight(50) };
    bounds.reduce(4, 4);
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
        m_colour = colourSelector->getCurrentColour();
        repaint();
    }
}

//-------------------------------------------------------------------------------------------------//
