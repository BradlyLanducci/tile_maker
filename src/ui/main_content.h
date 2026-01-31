#pragma once

#include <ui/components/top_bar.h>
#include <ui/components/directory_chooser.h>

#include <ui/editors/editor.h>

//-------------------------------------------------------------------------------------------------//

class MainContent : public juce::Component
{
public:
    MainContent();

    void paint(juce::Graphics &g) override;
    void resized() override;

private:
    void topBarSelectionChanged(Theme::EditorType type);

    TopBar m_topBar;
    std::unique_ptr<Editor> mp_editor{ nullptr };

    DirectoryChooser m_directoryChooser;
    juce::TextButton m_generate;
};

//-------------------------------------------------------------------------------------------------//
