#pragma once

#include <ui/components/image_drop_view.h>
#include <ui/components/titled_component.h>

#include <juce_gui_basics/juce_gui_basics.h>

//-------------------------------------------------------------------------------------------------//

class Masker : public juce::Component
{
public:
    Masker();

    void resized() override;

private:
    void imagesUpdated();

    TitledComponent m_input;
    TitledComponent m_mask;
    TitledComponent m_output;
};

//-------------------------------------------------------------------------------------------------//
