#pragma once

#include <ui/components/nine_slice.h>
#include <BinaryData.h>

#include <juce_gui_basics/juce_gui_basics.h>

//-------------------------------------------------------------------------------------------------//

class TitleBarLook : public juce::LookAndFeel_V4
{
public:
    void drawDocumentWindowTitleBar(juce::DocumentWindow &window, juce::Graphics &g, int, int, int, int,
                                    const juce::Image *, bool) override;

    juce::Button *createDocumentWindowButton(int buttonType) override;
};

//-------------------------------------------------------------------------------------------------//
