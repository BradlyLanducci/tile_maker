#include <ui/main_content.h>
#include <ui/editors/masker.h>
#include <ui/editors/blender.h>
#include <ui/utilities/theme.h>

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

    m_generate.onClick = [this]() {};
}

//-------------------------------------------------------------------------------------------------//

void MainContent::resized()
{
    auto bounds{ getLocalBounds() };
    m_topBar.setBounds(bounds.removeFromTop(50));
    if (mp_editor)
    {
        mp_editor->setBounds(bounds.removeFromTop(500));
    }
    m_directoryChooser.setBounds(bounds.removeFromLeft(getWidth() / 2));
    m_generate.setBounds(bounds);
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

    case Theme::EditorType::None:
    default:
        return;
    }

    addAndMakeVisible(*mp_editor);
    resized();
}

//-------------------------------------------------------------------------------------------------//
