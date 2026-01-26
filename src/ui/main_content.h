#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

//-------------------------------------------------------------------------------------------------//

class MainContent : public juce::Component
{
public:
    MainContent();

    void resized() override;

private:
    enum class EditorType : uint32_t
    {
        None = 0,
        Masker = 1,
        Blender = 2
    };

    juce::ComboBox m_editorSelector;
    std::unique_ptr<juce::Component> mp_editor{ nullptr };
};

//-------------------------------------------------------------------------------------------------//
