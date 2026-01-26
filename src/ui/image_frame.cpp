#include <ui/image_frame.h>

//-------------------------------------------------------------------------------------------------//

ImageFrame::ImageFrame(const juce::String &imagePath)
    : m_imagePath(imagePath)
{
}

//-------------------------------------------------------------------------------------------------//

void ImageFrame::paint(juce::Graphics &g)
{
    juce::Image image{ juce::ImageFileFormat::loadFrom(m_imagePath) };
    g.drawImage(image, getBounds().toFloat());
}

//-------------------------------------------------------------------------------------------------//
