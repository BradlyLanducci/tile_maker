#pragma once

#include <ui/components/top_bar.h>
#include <ui/components/directory_chooser.h>
#include <ui/theme/nine_slice_look.h>
#include <ui/editors/editor.h>

//-------------------------------------------------------------------------------------------------//

class MainContent : public juce::Component
{
public:
    MainContent();
    ~MainContent() override;

    void paint(juce::Graphics &g) override;
    void resized() override;

private:
    void topBarSelectionChanged(Theme::EditorType type);

    TopBar m_topBar;
    std::unique_ptr<Editor> mp_editor{ nullptr };

    DirectoryChooser m_directoryChooser;

    NineSliceLook m_look;
    juce::TextButton m_generate;
};

//-------------------------------------------------------------------------------------------------//
