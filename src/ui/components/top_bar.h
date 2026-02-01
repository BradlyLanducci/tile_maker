#pragma once

#include <ui/editors/editor.h>
#include <ui/theme/nine_slice_look.h>

#include <juce_gui_basics/juce_gui_basics.h>
#include <functional>

//-------------------------------------------------------------------------------------------------//

using SelectedCallback = std::function<void(Editor::Type)>;

//-------------------------------------------------------------------------------------------------//

class TopBar final : public juce::Component
{
public:
    explicit TopBar(SelectedCallback selectedCb);
    ~TopBar() override;

    void resized() override;

private:
    juce::FlexBox m_hBox;
    std::vector<juce::FlexItem> m_flexItems;
    std::vector<std::unique_ptr<juce::Component>> m_buttons;
    SelectedCallback m_selectedCb{ nullptr };

    NineSliceLook m_look;
};

//-------------------------------------------------------------------------------------------------//
