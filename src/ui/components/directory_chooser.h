#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

//-------------------------------------------------------------------------------------------------//

class DirectoryChooser final : public juce::Component
{
public:
    DirectoryChooser();

    void paint(juce::Graphics &g) override;
    void resized() override;

    juce::String getOutputDirectory() const;

private:
    juce::TextButton m_button;
    juce::FileChooser m_chooser;
    juce::String m_selectedDirectory;
};

//-------------------------------------------------------------------------------------------------//
