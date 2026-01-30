#include <ui/components/image_list.h>

//-------------------------------------------------------------------------------------------------//

ImageList::ImageList(std::unique_ptr<juce::ListBoxModel> p_model)
    : mp_model(std::move(p_model))
    , m_list("images", mp_model.get())
{
    m_list.setColour(juce::ListBox::ColourIds::backgroundColourId, juce::Colours::transparentBlack);
    addAndMakeVisible(m_list);
    m_list.updateContent();
    m_list.selectRow(0);
}

//-------------------------------------------------------------------------------------------------//

void ImageList::resized()
{
    m_list.setBounds(getBounds());
}

//-------------------------------------------------------------------------------------------------//
