#include <ui/main_content.h>
#include <ui/editors/masker.h>
#include <ui/editors/blender.h>

//-------------------------------------------------------------------------------------------------//

MainContent::MainContent()
{
    addAndMakeVisible(m_editorSelector);

    m_editorSelector.addItem("Masker", (int)EditorType::Masker);
    m_editorSelector.addItem("Blender", (int)EditorType::Blender);

    m_editorSelector.onChange = [this]()
    {
        EditorType selected{ static_cast<EditorType>(m_editorSelector.getSelectedId()) };

        switch (selected)
        {
        case EditorType::Masker:
            mp_editor = std::make_unique<Masker>();
            break;
        case EditorType::Blender:
            mp_editor = std::make_unique<Blender>();
            break;
        case EditorType::None:
        default:
            mp_editor = nullptr;
            break;
        }

        if (mp_editor)
        {
            addAndMakeVisible(*mp_editor);
            resized();
        }
    };

    m_editorSelector.setSelectedId((int)EditorType::Masker);
}

//-------------------------------------------------------------------------------------------------//

void MainContent::resized()
{
    auto bounds{ getLocalBounds() };
    m_editorSelector.setBounds(bounds.removeFromTop(50));
    if (mp_editor)
    {
        mp_editor->setBounds(bounds);
    }
}

//-------------------------------------------------------------------------------------------------//
