#pragma once

#include <ui/image_handler.h>

#include <juce_gui_basics/juce_gui_basics.h>

//-------------------------------------------------------------------------------------------------//

class Masker : public juce::Component
{
public:
    Masker();

    void resized() override;

private:
    ImageHandler m_input;
    ImageHandler m_mask;
};

//-------------------------------------------------------------------------------------------------//
