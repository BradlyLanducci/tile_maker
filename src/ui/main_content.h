#pragma once

#include <ui/components/top_bar.h>
#include <ui/components/directory_chooser.h>

#include <juce_gui_basics/juce_gui_basics.h>

//-------------------------------------------------------------------------------------------------//

class MainContent : public juce::Component
{
public:
    MainContent();

    void resized() override;

private:
    void topBarSelectionChanged(Theme::EditorType type);

    TopBar m_topBar;
    std::unique_ptr<juce::Component> mp_editor{ nullptr };

    DirectoryChooser m_directoryChooser;
    juce::TextButton m_generate;
};

//-------------------------------------------------------------------------------------------------//
