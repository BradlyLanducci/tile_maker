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

    void drawComboBox(juce::Graphics &, int width, int height, bool isButtonDown, int buttonX, int buttonY, int buttonW,
                      int buttonH, juce::ComboBox &) override;

    void drawLinearSlider(juce::Graphics &g, int x, int y, int width, int height, float sliderPos, float minSliderPos,
                          float maxSliderPos, juce::Slider::SliderStyle sliderStyle, juce::Slider &slider) override;

    void drawPopupMenuBackground(juce::Graphics &g, int width, int height) override;

    void drawPopupMenuItem(juce::Graphics &, const juce::Rectangle<int> &area, bool isSeparator, bool isActive,
                           bool isHighlighted, bool isTicked, bool hasSubMenu, const juce::String &text,
                           const juce::String &shortcutKeyText, const juce::Drawable *icon,
                           const juce::Colour *textColour) override;

private:
    NineSlice m_slice;
};

//-------------------------------------------------------------------------------------------------//
