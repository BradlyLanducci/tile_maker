#include <ui/components/top_bar.h>
#include <ui/utilities/theme.h>

#include <magic_enum/magic_enum.hpp>

//-------------------------------------------------------------------------------------------------//

constexpr std::vector<std::unique_ptr<juce::Component>> CreateButtons()
{
    std::vector<std::unique_ptr<juce::Component>> buttons;
    for (const auto type : magic_enum::enum_values<Theme::EditorType>())
    {
        if (type != Theme::EditorType::None)
        {
            buttons.emplace_back(std::make_unique<juce::TextButton>(
                juce::String{ magic_enum::enum_name<Theme::EditorType>(type).data() }));
        }
    }
    return buttons;
}

//-------------------------------------------------------------------------------------------------//

TopBar::TopBar(SelectedCallback selectedCb)
    : m_buttons{ CreateButtons() }
    , m_selectedCb(selectedCb)
{
    m_hBox.flexDirection = juce::FlexBox::Direction::row;
    m_hBox.justifyContent = juce::FlexBox::JustifyContent::flexStart;
    m_hBox.alignItems = juce::FlexBox::AlignItems::center;

    for (const auto &p_button : m_buttons)
    {
        juce::TextButton *p_textButton{ dynamic_cast<juce::TextButton *>(p_button.get()) };

        if (p_textButton)
        {
            p_textButton->onClick = [this, p_textButton]()
            {
                auto type{ magic_enum::enum_cast<Theme::EditorType>(p_textButton->getButtonText().toStdString()) };
                if (type)
                {
                    m_selectedCb(type.value());
                }
            };

            addAndMakeVisible(*p_button);
            juce::FlexItem &flexitem{ m_flexItems.emplace_back(*p_button) };
            m_hBox.items.add(flexitem.withMinWidth(200.f).withMinHeight(25.f));
        }
    }
}

//-------------------------------------------------------------------------------------------------//

void TopBar::paint(juce::Graphics &g)
{
    g.setFont(Theme::BIG_FONT_SIZE);
    g.setColour(juce::Colours::white);
    g.drawText("Iso Tile Maker", getLocalBounds().removeFromRight(Theme::TITLE_WIDTH), juce::Justification::centred);
}

//-------------------------------------------------------------------------------------------------//

void TopBar::resized()
{
    m_hBox.performLayout(getLocalBounds().removeFromLeft(getWidth() - Theme::TITLE_WIDTH));
}

//-------------------------------------------------------------------------------------------------//
