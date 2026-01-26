#pragma once

#include <ui/masker.h>

#include <juce_gui_basics/juce_gui_basics.h>
#include <memory>

//-------------------------------------------------------------------------------------------------//

class MainWindow : public juce::DocumentWindow
{
public:
    MainWindow(juce::String name);

    void closeButtonPressed();

private:
    Masker m_masker;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainWindow)
};

//-------------------------------------------------------------------------------------------------//