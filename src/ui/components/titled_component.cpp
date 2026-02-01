#include <ui/components/titled_component.h>
#include <ui/theme/theme.h>
#include <BinaryData.h>

//-------------------------------------------------------------------------------------------------//

constexpr int TEXT_SIZE{ 25 };

//-------------------------------------------------------------------------------------------------//

TitledComponent::TitledComponent(const juce::String &title, std::unique_ptr<juce::Component> p_component,
                                 bool drawBackground)
    : m_title(title)
    , m_slice(BinaryData::nine_slice_panel_png, BinaryData::nine_slice_panel_pngSize)
    , mp_component(std::move(p_component))
    , m_drawBackground(drawBackground)
{
    addAndMakeVisible(*mp_component);
}

//-------------------------------------------------------------------------------------------------//

void TitledComponent::paint(juce::Graphics &g)
{
    if (m_drawBackground)
    {
        m_slice.draw(g, getLocalBounds());
        g.setFont(Theme::BIG_FONT_SIZE);
    }
    else
    {
        g.setFont(Theme::NORMAL_FONT_SIZE);
    }

    auto bounds{ getBounds() };
    g.setColour(Theme::LIGHT_TEXT);
    g.drawText(m_title, 0, (int)g.getCurrentFont().getHeight() / 2, bounds.getWidth(), TEXT_SIZE,
               juce::Justification::centred);
}

//-------------------------------------------------------------------------------------------------//

void TitledComponent::resized()
{
    auto bounds{ getBounds() };
    bounds = bounds.removeFromBottom(bounds.getHeight() - TEXT_SIZE);
    bounds.reduce(Theme::DEFAULT_PADDING, Theme::DEFAULT_PADDING);
    mp_component->setBounds(Theme::DEFAULT_PADDING, TEXT_SIZE + Theme::DEFAULT_PADDING, bounds.getWidth(),
                            bounds.getHeight());
}

//-------------------------------------------------------------------------------------------------//
