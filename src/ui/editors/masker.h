#pragma once

#include <ui/components/image_drop_view.h>
#include <ui/components/titled_component.h>

#include <juce_gui_basics/juce_gui_basics.h>

//-------------------------------------------------------------------------------------------------//

class Masker final : public juce::Component
{
public:
    Masker();

    void resized() override;

private:
    std::unique_ptr<juce::Component> imagesUpdated(juce::Component *p_caller, juce::ValueTree tree);

    juce::ValueTree m_tree;

    TitledComponent m_output;
    std::unique_ptr<TitledComponent> mp_input;
    std::unique_ptr<TitledComponent> mp_mask;
};

//-------------------------------------------------------------------------------------------------//
