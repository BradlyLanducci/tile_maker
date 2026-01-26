#pragma once

#include <ui/components/image_drop_view.h>
#include <ui/components/titled_component.h>

#include <juce_gui_basics/juce_gui_basics.h>

//-------------------------------------------------------------------------------------------------//

class Blender : public juce::Component
{
public:
    Blender();

    void resized() override;

private:
    void imagesUpdated();

    TitledComponent m_inputs;
    TitledComponent m_template;
    TitledComponent m_output;
};

//-------------------------------------------------------------------------------------------------//
