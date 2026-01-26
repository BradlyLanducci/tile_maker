#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

//-------------------------------------------------------------------------------------------------//

struct ImageData;

//-------------------------------------------------------------------------------------------------//

class ImageFrame : public juce::Component
{
public:
    ImageFrame() = default;
    ImageFrame(std::unique_ptr<ImageData> imageData);

    void paint(juce::Graphics &g) override;

    void setImage(std::unique_ptr<ImageData> p_imageData);
    void reset();

private:
    juce::Image m_image;
};

//-------------------------------------------------------------------------------------------------//
