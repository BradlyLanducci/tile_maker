#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

namespace Theme
{
    const juce::Identifier FORCE_UPDATE{ "force_update" };
    const juce::Identifier COLOUR_KEY{ "colour" };
    const juce::Identifier SELECTED_KEY{ "selected" };

    constexpr int DEFAULT_WINDOW_WIDTH{ 1440 };
    constexpr int DEFAULT_WINDOW_HEIGHT{ 810 };

    constexpr int TITLE_WIDTH{ 200 };
    constexpr int NORMAL_FONT_SIZE{ 16 };
    constexpr int BIG_FONT_SIZE{ 32 };
    constexpr int HUMONGOUS_FONT_SIZE{ 128 };

    constexpr int DEFAULT_PADDING{ 4 };

    const juce::Colour DARK_PURPLE{ juce::Colour(25, 24, 39) };
    const juce::Colour LIGHT_TEXT{ juce::Colours::white };
    const juce::Colour DARK_TEXT{ juce::Colours::black };
}
