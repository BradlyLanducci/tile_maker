#include <ui/components/titled_component.h>
#include <ui/utilities/theme.h>
#include <BinaryData.h>

//-------------------------------------------------------------------------------------------------//

constexpr int TEXT_SIZE{ 25 };

//-------------------------------------------------------------------------------------------------//

TitledComponent::TitledComponent(const juce::String &title, std::unique_ptr<juce::Component> p_component)
    : m_title(title)
    , m_slice(BinaryData::nine_slice_panel_png, BinaryData::nine_slice_panel_pngSize)
    , mp_component(std::move(p_component))
{
    addAndMakeVisible(*mp_component);
}

//-------------------------------------------------------------------------------------------------//

void TitledComponent::paint(juce::Graphics &g)
{
    m_slice.draw(g, getLocalBounds());
    auto bounds{ getBounds() };
    g.setFont(Theme::BIG_FONT_SIZE);
    g.setColour(juce::Colours::white);
    g.drawText(m_title, 0, 0, bounds.getWidth(), TEXT_SIZE, juce::Justification::centred);
}

//-------------------------------------------------------------------------------------------------//

void TitledComponent::resized()
{
    auto bounds{ getBounds() };
    bounds = bounds.removeFromBottom(bounds.getHeight() - TEXT_SIZE);
    const int padding{ 4 };
    bounds.reduce(padding, padding);
    mp_component->setBounds(padding, TEXT_SIZE + padding, bounds.getWidth(), bounds.getHeight());
}

//-------------------------------------------------------------------------------------------------//
