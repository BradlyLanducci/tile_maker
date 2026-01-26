#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

//-------------------------------------------------------------------------------------------------//

class TitledComponent : public juce::Component
{
public:
    TitledComponent(const juce::String &title, juce::Component *p_component);

    void paint(juce::Graphics &g) override;
    void resized() override;

    juce::Component *getComponent();

private:
    juce::String m_title;
    std::unique_ptr<juce::Component> mp_component;
};

//-------------------------------------------------------------------------------------------------//
