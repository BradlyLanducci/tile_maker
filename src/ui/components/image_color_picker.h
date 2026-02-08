#pragma once

#include <ui/theme/nine_slice_look.h>

#include <juce_gui_basics/juce_gui_basics.h>

//-------------------------------------------------------------------------------------------------//

class ImageColorPicker final
    : public juce::Component
    , public juce::ChangeListener
{
public:
    explicit ImageColorPicker(juce::ValueTree tree);

    void paint(juce::Graphics &g) override;

    void mouseUp(const juce::MouseEvent &event) override;

    void changeListenerCallback(juce::ChangeBroadcaster *source) override;

private:
    juce::ValueTree m_tree;

    NineSliceLook m_look;
};

//-------------------------------------------------------------------------------------------------//
