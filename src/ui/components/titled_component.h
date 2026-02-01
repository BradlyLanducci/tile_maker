#pragma once

#include <ui/components/nine_slice.h>

#include <juce_gui_basics/juce_gui_basics.h>

//-------------------------------------------------------------------------------------------------//

class TitledComponent final : public juce::Component
{
public:
    explicit TitledComponent(const juce::String &title, std::unique_ptr<juce::Component> p_component,
                             bool drawBackground = true);

    void paint(juce::Graphics &g) override;
    void resized() override;

    template <typename ComponentType> ComponentType *getComponent() const
    {
        return static_cast<ComponentType *>(mp_component.get());
    }

private:
    juce::String m_title;
    NineSlice m_slice;
    std::unique_ptr<juce::Component> mp_component;

    bool m_drawBackground;
};

//-------------------------------------------------------------------------------------------------//
