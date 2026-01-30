#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

//-------------------------------------------------------------------------------------------------//

class ImageList final : public juce::Component
{
public:
    explicit ImageList(std::unique_ptr<juce::ListBoxModel> p_model);

    void resized() override;

private:
    std::unique_ptr<juce::ListBoxModel> mp_model;
    juce::ListBox m_list;
};

//-------------------------------------------------------------------------------------------------//
