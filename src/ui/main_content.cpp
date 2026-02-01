#include <ui/main_content.h>
#include <ui/editors/masker.h>
#include <ui/editors/blender.h>
#include <ui/editors/noiser.h>
#include <ui/theme/theme.h>
#include <BinaryData.h>

#include <magic_enum/magic_enum.hpp>

//-------------------------------------------------------------------------------------------------//

MainContent::MainContent()
    : m_animator(this)
    , m_topBar([this](Editor::Type type) { setEditor(type); })
    , mp_editor(std::make_unique<Masker>())
    , m_generate("Generate")
    , m_scaler("Scale", std::make_unique<juce::ComboBox>(), false)
{
    m_directoryChooser.setLookAndFeel(&m_look);
    m_generate.setLookAndFeel(&m_look);
    m_scaler.setLookAndFeel(&m_look);

    m_generate.onClick = [this]()
    {
        if (mp_editor)
        {
            mp_editor->generate(m_directoryChooser.getOutputDirectory());
        }
    };

    auto p_scaler{ m_scaler.getComponent<juce::ComboBox>() };
    p_scaler->addItem("75%", 1);
    p_scaler->addItem("100%", 2);
    p_scaler->addItem("125%", 3);
    p_scaler->addItem("150%", 4);
    p_scaler->addItem("200%", 5);
    p_scaler->setSelectedId(2);
    p_scaler->onChange = [this, p_scaler]()
    {
        auto p_window{ findParentComponentOfClass<juce::DocumentWindow>() };

        float scalar{ 1.f };

        switch (p_scaler->getSelectedId())
        {
        case 1: // 75%
            scalar = 0.75f;
            break;
        case 3: // 125%
            scalar = 1.25f;
            break;
        case 4: // 150%
            scalar = 1.5f;
            break;
        case 5: // 200%
            scalar = 2.f;
            break;
        default:
            break;
        }

        juce::Desktop::getInstance().setGlobalScaleFactor(scalar);
        p_window->setSize((int)(scalar * (float)Theme::DEFAULT_WINDOW_WIDTH),
                          (int)(scalar * (float)Theme::DEFAULT_WINDOW_HEIGHT));
    };

    addAndMakeVisible(m_animator);
    addAndMakeVisible(m_topBar);
    addAndMakeVisible(*mp_editor);
    addAndMakeVisible(m_directoryChooser);
    addAndMakeVisible(m_generate);
    addAndMakeVisible(m_scaler);
}

//-------------------------------------------------------------------------------------------------//

MainContent::~MainContent()
{
    m_directoryChooser.setLookAndFeel(nullptr);
    m_generate.setLookAndFeel(nullptr);
    m_scaler.setLookAndFeel(nullptr);
}

//-------------------------------------------------------------------------------------------------//

void MainContent::paint(juce::Graphics &g)
{
    auto bounds{ getLocalBounds().toFloat() };
    m_animator.draw(g, bounds);
}

//-------------------------------------------------------------------------------------------------//

void MainContent::resized()
{
    auto bounds{ getLocalBounds() };

    auto top{ bounds.removeFromTop(75) };
    top.reduce(Theme::DEFAULT_PADDING, Theme::DEFAULT_PADDING);
    m_topBar.setBounds(top);

    auto bottom{ bounds.removeFromBottom(100).removeFromRight(575) };

    m_directoryChooser.setBounds(bottom.removeFromLeft(200).reduced(10).withWidth(180));
    m_generate.setBounds(bottom.removeFromLeft(200).removeFromBottom(75).reduced(10).withWidth(180));
    m_scaler.setBounds(bottom.reduced(6));

    if (mp_editor)
    {
        const int editorPadding{ 50 };
        bounds.reduce(editorPadding, editorPadding);
        mp_editor->setBounds(bounds);
    }
}

//-------------------------------------------------------------------------------------------------//

void MainContent::setEditor(Editor::Type type)
{
    m_animator.animate(type);

    switch (type)
    {
    case Editor::Type::Masker:
        mp_editor = std::make_unique<Masker>();
        break;
    case Editor::Type::Blender:
        mp_editor = std::make_unique<Blender>();
        break;
    case Editor::Type::Noiser:
        mp_editor = std::make_unique<Noiser>();
        break;
    case Editor::Type::None:
    default:
        return;
    }

    addAndMakeVisible(*mp_editor);
    repaint();
    resized(); // This feels wrong, but has caused no issues so far...
}

//-------------------------------------------------------------------------------------------------//
