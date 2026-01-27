#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

//-------------------------------------------------------------------------------------------------//

template <typename ModelType> class ImageList final : public juce::Component
{
public:
    explicit ImageList(juce::ValueTree tree)
        : m_model(tree)
        , m_list("images", &m_model)
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
    ModelType m_model;
    juce::ListBox m_list;
};

//-------------------------------------------------------------------------------------------------//
