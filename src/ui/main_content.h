#pragma once

#include <ui/components/top_bar.h>
#include <ui/components/directory_chooser.h>
#include <ui/theme/nine_slice_look.h>
#include <ui/editors/editor.h>
#include <ui/components/background_animation.h>
#include <ui/components/titled_component.h>

#include <ui/components/tree_view.h>

//-------------------------------------------------------------------------------------------------//

class MainContent : public juce::Component
{
public:
    MainContent();
    ~MainContent() override;

    void paint(juce::Graphics &g) override;
    void resized() override;

private:
    void setEditor(Editor::Type type);

    Editor::Type m_editorType;

    // BackgroundAnimation m_animator;

    TopBar m_topBar;

    DirectoryChooser m_directoryChooser;

    NineSliceLook m_look;
    juce::TextButton m_generate;

    TitledComponent m_scaler;

    TreeView m_view;
};

//-------------------------------------------------------------------------------------------------//
