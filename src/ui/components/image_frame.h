#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

//-------------------------------------------------------------------------------------------------//

struct ImageData;

//-------------------------------------------------------------------------------------------------//

class ImageFrame : public juce::Component
{
public:
    ImageFrame() = default;
    ImageFrame(std::unique_ptr<ImageData> p_imageData);

    void paint(juce::Graphics &g) override;

    void setImage(std::unique_ptr<ImageData> p_imageData);
    void reset();

private:
    // Converts stbi RGBA to JUCE ARGB
    void RGBAToARGB(ImageData *p_imageData);

    // Converts stbi RGB to JUCE RGB
    void RGBToRGB(ImageData *p_imageData);

    juce::Image m_image;
};

//-------------------------------------------------------------------------------------------------//
