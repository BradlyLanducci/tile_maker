#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

//-------------------------------------------------------------------------------------------------//

class TitledComponent final : public juce::Component
{
public:
    explicit TitledComponent(const juce::String &title, juce::Component *p_component);

    void paint(juce::Graphics &g) override;
    void resized() override;

    template <typename ComponentType> ComponentType *getComponent() const
    {
        return static_cast<ComponentType *>(mp_component.get());
    }

private:
    juce::String m_title;
    std::unique_ptr<juce::Component> mp_component;
};

//-------------------------------------------------------------------------------------------------//
