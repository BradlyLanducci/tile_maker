#pragma once

#include <ui/components/image_drop_view.h>
#include <ui/components/titled_component.h>
#include <ui/editors/editor.h>

//-------------------------------------------------------------------------------------------------//

class Masker final : public Editor
{
public:
    Masker();

    void resized() override;

    void generate(const juce::String &baseOutputDirectory) override;

private:
    std::unique_ptr<juce::Component> dropViewChanged(juce::ValueTree tree);

    juce::ValueTree m_tree;

    TitledComponent m_output;
    std::unique_ptr<TitledComponent> mp_input;
    std::unique_ptr<TitledComponent> mp_mask;
};

//-------------------------------------------------------------------------------------------------//
