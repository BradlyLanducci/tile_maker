#pragma once

#include <ui/components/image_drop_view.h>
#include <ui/components/titled_component.h>
#include <ui/editors/editor.h>

//-------------------------------------------------------------------------------------------------//

class Blender final
    : public Editor
    , public juce::ValueTree::Listener
{
public:
    Blender();

    void resized() override;

    void generate(const juce::String &baseOutputDirectory) override;

private:
    [[nodiscard]] std::unique_ptr<juce::Component> dropViewChanged(juce::Component *p_caller, juce::ValueTree tree);

    void valueTreePropertyChanged(juce::ValueTree &treeWhosePropertyHasChanged,
                                  const juce::Identifier &property) override;

    juce::ValueTree m_tree;

    TitledComponent m_output;
    std::unique_ptr<TitledComponent> mp_inputs;
    std::unique_ptr<TitledComponent> mp_templates;
};

//-------------------------------------------------------------------------------------------------//
