#include <ui/components/titled_component.h>

//-------------------------------------------------------------------------------------------------//

constexpr int TEXT_SIZE{ 25 };

//-------------------------------------------------------------------------------------------------//

TitledComponent::TitledComponent(const juce::String &title, juce::Component *p_component)
    : m_title(title)
    , mp_component(p_component)
{
    addAndMakeVisible(*mp_component);
}

//-------------------------------------------------------------------------------------------------//

void TitledComponent::paint(juce::Graphics &g)
{
    g.fillAll(juce::Colours::darkslategrey);
    auto bounds{ getBounds() };
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
