#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

//-------------------------------------------------------------------------------------------------//

class ImageList final : public juce::Component
{
public:
    explicit ImageList(std::unique_ptr<juce::ListBoxModel> p_model)
        : mp_model(std::move(p_model))
        , m_list("images", mp_model.get())
    {
        m_list.setColour(juce::ListBox::ColourIds::backgroundColourId, juce::Colours::transparentBlack);
        addAndMakeVisible(m_list);
        m_list.updateContent();
    }

    void resized() override
    {
        m_list.setBounds(getBounds());
    }

private:
    std::unique_ptr<juce::ListBoxModel> mp_model;
    juce::ListBox m_list;
};

//-------------------------------------------------------------------------------------------------//
