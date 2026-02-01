#include <ui/theme/nine_slice_look.h>
#include <ui/theme/theme.h>
#include <BinaryData.h>

//-------------------------------------------------------------------------------------------------//

NineSliceLook::NineSliceLook()
    : m_slice(BinaryData::nine_slice_panel_png, BinaryData::nine_slice_panel_pngSize)
{
}

//-------------------------------------------------------------------------------------------------//

void NineSliceLook::drawButtonBackground(juce::Graphics &g, juce::Button &button, const juce::Colour &colour,
                                         bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
{
    (void)colour;
    (void)shouldDrawButtonAsDown;
    if (shouldDrawButtonAsHighlighted)
    {
        g.setOpacity(0.75f);
        g.setColour(juce::Colour(0, 0, 0).withAlpha(0.5f));
    }

    m_slice.draw(g, button.getLocalBounds());
    g.setOpacity(1.f);
}

//-------------------------------------------------------------------------------------------------//

void NineSliceLook::drawComboBox(juce::Graphics &g, int, int, bool, int, int, int, int, juce::ComboBox &combo)
{
    m_slice.draw(g, combo.getLocalBounds());
}

//-------------------------------------------------------------------------------------------------//

void NineSliceLook::drawLinearSlider(juce::Graphics &g, int x, int y, int width, int height, float sliderPos,
                                     float minSliderPos, float maxSliderPos, juce::Slider::SliderStyle sliderStyle,
                                     juce::Slider &slider)
{
    juce::LookAndFeel_V4::drawLinearSlider(g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, sliderStyle,
                                           slider);

    float centerHeight{ (float)height / 2.f };

    const int sideLength{ 16 };
    juce::Image image{ juce::ImageCache::getFromMemory(BinaryData::thumb_png, BinaryData::thumb_pngSize) };
    g.drawImage(image, juce::Rectangle<float>(sliderPos - sideLength / 2, centerHeight - sideLength / 2, sideLength,
                                              sideLength));
}

//-------------------------------------------------------------------------------------------------//

void NineSliceLook::drawPopupMenuBackground(juce::Graphics &g, int, int)
{
    g.fillAll(Theme::DARK_PURPLE);
}

//-------------------------------------------------------------------------------------------------//

void NineSliceLook::drawPopupMenuItem(juce::Graphics &g, const juce::Rectangle<int> &area, bool, bool,
                                      bool isHighlighted, bool, bool, const juce::String &text, const juce::String &,
                                      const juce::Drawable *, const juce::Colour *)
{
    if (isHighlighted)
    {
        g.fillAll(Theme::LIGHT_TEXT);
        g.setColour(Theme::DARK_TEXT);
    }
    else
    {
        g.fillAll(juce::Colours::transparentBlack);
        g.setColour(Theme::LIGHT_TEXT);
    }
    auto bounds{ area };
    g.setFont(Theme::NORMAL_FONT_SIZE);
    g.drawText(text, bounds.removeFromRight(bounds.getWidth() - Theme::DEFAULT_PADDING), juce::Justification::left);
}

//-------------------------------------------------------------------------------------------------//
