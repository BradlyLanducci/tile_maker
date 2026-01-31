#include <ui/theme/title_bar_look.h>
#include <ui/theme/theme.h>

//-------------------------------------------------------------------------------------------------//

void TitleBarLook::drawDocumentWindowTitleBar(juce::DocumentWindow &window, juce::Graphics &g, int, int, int, int,
                                              const juce::Image *, bool)
{
    g.fillAll(Theme::DARK_PURPLE);
    g.setColour(Theme::LIGHT_TEXT);
    g.drawText("Iso Tile Maker", window.getTitleBarArea(), juce::Justification::centred);
}

//-------------------------------------------------------------------------------------------------//

juce::Button *TitleBarLook::createDocumentWindowButton(int buttonType)
{
    juce::Path shape;
    const float crossThickness = 0.05f;

    juce::ShapeButton *p_button{ nullptr };

    if (buttonType == juce::DocumentWindow::closeButton)
    {
        shape.addLineSegment(juce::Line<float>(0.25f, 0.25f, 0.75f, 0.75f), crossThickness);
        shape.addLineSegment(juce::Line<float>(0.75f, 0.25f, 0.25f, 0.75f), crossThickness);

        p_button =
            new juce::ShapeButton("close", Theme::LIGHT_TEXT, Theme::LIGHT_TEXT.withAlpha(0.5f), Theme::LIGHT_TEXT);
    }

    if (buttonType == juce::DocumentWindow::minimiseButton)
    {
        shape.addLineSegment(juce::Line<float>(0.25f, 0.5f, 0.75f, 0.5f), crossThickness);

        p_button =
            new juce::ShapeButton("minimize", Theme::LIGHT_TEXT, Theme::LIGHT_TEXT.withAlpha(0.5f), Theme::LIGHT_TEXT);
    }

    if (p_button)
    {
        p_button->setShape(shape, true, true, false);
    }

    return p_button;
}

//-------------------------------------------------------------------------------------------------//
