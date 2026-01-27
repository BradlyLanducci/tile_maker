#pragma once

#include <ui/utilities/theme.h>

#include <juce_gui_basics/juce_gui_basics.h>
#include <functional>

//-------------------------------------------------------------------------------------------------//

using SelectedCallback = std::function<void(Theme::EditorType)>;

//-------------------------------------------------------------------------------------------------//

class TopBar final : public juce::Component
{
public:
    explicit TopBar(SelectedCallback selectedCb);

    void paint(juce::Graphics &g) override;
    void resized() override;

private:
    juce::FlexBox m_hBox;
    std::vector<juce::FlexItem> m_flexItems;
    std::vector<std::unique_ptr<juce::Component>> m_buttons;
    SelectedCallback m_selectedCb{ nullptr };
};

//-------------------------------------------------------------------------------------------------//
