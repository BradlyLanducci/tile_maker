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
    std::unique_ptr<juce::Component> imagesUpdated(juce::Component *p_caller, const juce::StringArray &files);

    TitledComponent m_inputsA;
    TitledComponent m_inputsB;
    TitledComponent m_template;
    TitledComponent m_output;
};

//-------------------------------------------------------------------------------------------------//
