#include <ui/theme/nine_slice_look.h>

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
