#include <ui/image_list_container.h>

//-------------------------------------------------------------------------------------------------//

ImageListContainer::ImageListContainer(const juce::StringArray &images)
    : m_model(images)
    , m_list(m_model)
{
    m_list.setColour(juce::ListBox::ColourIds::backgroundColourId, juce::Colours::transparentBlack);
    addAndMakeVisible(m_list);
    m_list.updateContent();
}

//-------------------------------------------------------------------------------------------------//

void ImageListContainer::resized()
{
    m_list.setBounds(getBounds());
}

//-------------------------------------------------------------------------------------------------//
