#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

//-------------------------------------------------------------------------------------------------//

class ImageFrame : public juce::Component
{
public:
    ImageFrame(const juce::String &imagePath);

    void paint(juce::Graphics &g) override;

private:
    juce::String m_imagePath;
};

//-------------------------------------------------------------------------------------------------//
