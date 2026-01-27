#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

namespace Theme
{
    const juce::Identifier FORCE_UPDATE{ "force_update" };
    const juce::Identifier COLOUR_KEY{ "colour" };

    enum class EditorType : uint32_t
    {
        None = 0,
        Masker = 1,
        Blender = 2
    };

    constexpr int TITLE_WIDTH{ 100 };
}
