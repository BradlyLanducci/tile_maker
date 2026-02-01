#pragma once

#include <ui/components/image_drop_view.h>
#include <ui/components/titled_component.h>
#include <ui/editors/editor.h>
#include <processing/image_manipulation.h>
#include <ui/theme/nine_slice_look.h>

//-------------------------------------------------------------------------------------------------//

class Noiser final
    : public Editor
    , public juce::ValueTree::Listener
{
public:
    Noiser();
    ~Noiser() override;

    void resized() override;
    void generate(const juce::String &baseOutputDirectory) override;

private:
    [[nodiscard]] std::unique_ptr<juce::Component> dropViewChanged(juce::ValueTree tree);

    void valueTreePropertyChanged(juce::ValueTree &treeWhosePropertyHasChanged,
                                  const juce::Identifier &property) override;

    juce::String getSelectedInput();
    Noise getSelectedNoise();
    void updateOutput(const juce::String &input);

    juce::ValueTree m_tree;

    TitledComponent m_output;
    std::unique_ptr<TitledComponent> mp_inputs;

    TitledComponent m_noiseTypeCombo;
    TitledComponent m_opacitySlider;
    TitledComponent m_frequencySlider;
    TitledComponent m_seedSlider;
    NineSliceLook m_look;
};

//-------------------------------------------------------------------------------------------------//
