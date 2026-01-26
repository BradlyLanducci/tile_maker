#pragma once

#include <ui/main_content.h>

#include <juce_gui_basics/juce_gui_basics.h>
#include <memory>

//-------------------------------------------------------------------------------------------------//

class MainWindow : public juce::DocumentWindow
{
public:
    MainWindow(juce::String name);

    void closeButtonPressed();

private:
    MainContent m_content;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainWindow)
};

//-------------------------------------------------------------------------------------------------//