#include <ui/image_list.h>

//-------------------------------------------------------------------------------------------------//

ImageList::ImageList(const juce::StringArray &images)
    : m_model(images)
    , m_list("images", &m_model)
{
    addAndMakeVisible(m_list);
    m_list.updateContent();
}

//-------------------------------------------------------------------------------------------------//

void ImageList::resized()
{
    m_list.setBounds(getBounds());
}

//-------------------------------------------------------------------------------------------------//
