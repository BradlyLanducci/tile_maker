#include <ui/main_content.h>
#include <ui/editors/masker.h>
#include <ui/editors/blender.h>
#include <ui/editors/noiser.h>
#include <ui/theme/theme.h>

//-------------------------------------------------------------------------------------------------//

MainContent::MainContent()
    : m_topBar([this](Theme::EditorType type) { topBarSelectionChanged(type); })
    , mp_editor(std::make_unique<Masker>())
    , m_generate("Generate")
{
    addAndMakeVisible(m_topBar);
    addAndMakeVisible(*mp_editor);
    addAndMakeVisible(m_directoryChooser);
    addAndMakeVisible(m_generate);

    m_directoryChooser.setLookAndFeel(&m_look);
    m_generate.setLookAndFeel(&m_look);

    m_generate.onClick = [this]()
    {
        if (mp_editor)
        {
            mp_editor->generate(m_directoryChooser.getOutputDirectory());
        }
    };
}

//-------------------------------------------------------------------------------------------------//

MainContent::~MainContent()
{
    m_directoryChooser.setLookAndFeel(nullptr);
    m_generate.setLookAndFeel(nullptr);
}

//-------------------------------------------------------------------------------------------------//

void MainContent::paint(juce::Graphics &g)
{
    g.fillAll(juce::Colours::black);
}

//-------------------------------------------------------------------------------------------------//

void MainContent::resized()
{
    auto bounds{ getLocalBounds() };

    auto top{ bounds.removeFromTop(75) };
    top.reduce(Theme::DEFAULT_PADDING, Theme::DEFAULT_PADDING);
    m_topBar.setBounds(top);

    auto bottom{ bounds.removeFromBottom(100) };

    auto bottomLeft{ bottom.removeFromLeft(getWidth() / 2) };
    auto dirBounds{ bottomLeft.reduced(10).withWidth(200) };
    m_directoryChooser.setBounds(
        dirBounds.withX(dirBounds.getX() + (bottomLeft.getWidth() - dirBounds.getWidth()) / 2));

    auto genBounds{ bottom.removeFromBottom(75).reduced(10).withWidth(200) };
    m_generate.setBounds(genBounds.withX(genBounds.getX() + (bottom.getWidth() - genBounds.getWidth()) / 2));

    if (mp_editor)
    {
        const int editorPadding{ 50 };
        bounds.reduce(editorPadding, editorPadding);
        mp_editor->setBounds(bounds);
    }
}

//-------------------------------------------------------------------------------------------------//

void MainContent::topBarSelectionChanged(Theme::EditorType type)
{
    switch (type)
    {
    case Theme::EditorType::Masker:
        mp_editor = std::make_unique<Masker>();
        break;
    case Theme::EditorType::Blender:
        mp_editor = std::make_unique<Blender>();
        break;
    case Theme::EditorType::Noiser:
        mp_editor = std::make_unique<Noiser>();
        break;
    case Theme::EditorType::None:
    default:
        return;
    }

    addAndMakeVisible(*mp_editor);
    resized();
}

//-------------------------------------------------------------------------------------------------//
