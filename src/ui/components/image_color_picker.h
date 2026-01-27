#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

//-------------------------------------------------------------------------------------------------//

class ImageColorPicker
    : public juce::Component
    , public juce::ChangeListener
{
public:
    ImageColorPicker(juce::ValueTree tree);

    void paint(juce::Graphics &g) override;

    void mouseUp(const juce::MouseEvent &event) override;

    void changeListenerCallback(juce::ChangeBroadcaster *source) override;

private:
    juce::ValueTree m_tree;
};

//-------------------------------------------------------------------------------------------------//
