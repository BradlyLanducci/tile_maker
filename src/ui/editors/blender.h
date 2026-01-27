#pragma once

#include <ui/components/image_drop_view.h>
#include <ui/components/titled_component.h>

#include <juce_gui_basics/juce_gui_basics.h>

//-------------------------------------------------------------------------------------------------//

class Blender
    : public juce::Component
    , public juce::ValueTree::Listener
{
public:
    Blender();

    void resized() override;

private:
    std::unique_ptr<juce::Component> imagesUpdated(juce::Component *p_caller, juce::ValueTree tree);

    void valueTreePropertyChanged(juce::ValueTree &treeWhosePropertyHasChanged,
                                  const juce::Identifier &property) override;

    juce::ValueTree m_tree;

    TitledComponent m_output;
    std::unique_ptr<TitledComponent> mp_inputs;
    std::unique_ptr<TitledComponent> mp_templates;
};

//-------------------------------------------------------------------------------------------------//
