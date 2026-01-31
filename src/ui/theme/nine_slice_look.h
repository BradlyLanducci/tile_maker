#pragma once

#include <ui/components/nine_slice.h>
#include <BinaryData.h>

#include <juce_gui_basics/juce_gui_basics.h>

//-------------------------------------------------------------------------------------------------//

class NineSliceLook : public juce::LookAndFeel_V4
{
public:
    NineSliceLook();

    void drawButtonBackground(juce::Graphics &g, juce::Button &button, const juce::Colour &colour,
                              bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;

private:
    NineSlice m_slice;
};

//-------------------------------------------------------------------------------------------------//
