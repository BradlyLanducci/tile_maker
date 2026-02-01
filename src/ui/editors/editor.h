#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

//-------------------------------------------------------------------------------------------------//

class Editor : public juce::Component
{
public:
    enum class Type : uint32_t
    {
        None = 0,
        Masker = 1,
        Blender = 2,
        Noiser = 3
    };

    virtual void generate(const juce::String &baseOutputDirectory) = 0;
};

//-------------------------------------------------------------------------------------------------//
