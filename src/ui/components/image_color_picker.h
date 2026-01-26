#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

//-------------------------------------------------------------------------------------------------//

class ImageColorPicker
    : public juce::Component
    , public juce::ChangeListener
{
public:
    ImageColorPicker(const juce::String &imageName, juce::Colour defaultColour = juce::Colours::black);

    void paint(juce::Graphics &g) override;

    void mouseUp(const juce::MouseEvent &event) override;

    void changeListenerCallback(juce::ChangeBroadcaster *source) override;

private:
    juce::String m_imageName;
    juce::Colour m_colour;
};

//-------------------------------------------------------------------------------------------------//
