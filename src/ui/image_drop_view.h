#pragma once

#include <ui/image_handler.h>

//-------------------------------------------------------------------------------------------------//

class ImageDropView : public juce::Component
{
public:
    ImageDropView(const juce::String &title);

    void paint(juce::Graphics &g) override;
    void resized() override;

    juce::StringArray getImages();

private:
    juce::String m_title;
    ImageHandler m_handler;
};

//-------------------------------------------------------------------------------------------------//
