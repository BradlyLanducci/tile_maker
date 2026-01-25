#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include <memory>

//-------------------------------------------------------------------------------------------------//

class MainWindow : public juce::DocumentWindow
{
public:
    MainWindow(juce::String name);

    void closeButtonPressed();

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainWindow)
};

//-------------------------------------------------------------------------------------------------//