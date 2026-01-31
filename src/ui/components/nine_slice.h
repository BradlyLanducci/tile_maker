#pragma once

#include <cstdint>
#include <juce_gui_basics/juce_gui_basics.h>

//-------------------------------------------------------------------------------------------------//

class NineSlice
{
public:
    explicit NineSlice(const char *data, int bytes);
    void draw(juce::Graphics &g, const juce::Rectangle<int> &localBounds);

private:
    juce::Image m_image;
};

//-------------------------------------------------------------------------------------------------//
