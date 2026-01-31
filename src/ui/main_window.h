#pragma once

#include <ui/main_content.h>
#include <ui/theme/title_bar_look.h>

#include <juce_gui_basics/juce_gui_basics.h>
#include <memory>

//-------------------------------------------------------------------------------------------------//

class MainWindow : public juce::DocumentWindow
{
public:
    MainWindow(juce::String name);
    ~MainWindow() override;

    void closeButtonPressed() override;

private:
    MainContent m_content;
    TitleBarLook m_look;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainWindow)
};

//-------------------------------------------------------------------------------------------------//
