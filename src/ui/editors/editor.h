#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

//-------------------------------------------------------------------------------------------------//

class Editor : public juce::Component
{
public:
    virtual void generate(const juce::String &baseOutputDirectory) = 0;
};

//-------------------------------------------------------------------------------------------------//
