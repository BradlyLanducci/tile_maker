#pragma once

#include <ui/main_window.h>

//-------------------------------------------------------------------------------------------------//

class App : public juce::JUCEApplication
{
public:
    void initialise(const juce::String &commandLine) override;
    void shutdown() override;
    const juce::String getApplicationName() override;
    const juce::String getApplicationVersion() override;

private:
    std::unique_ptr<MainWindow> mp_window;
};

//-------------------------------------------------------------------------------------------------//

START_JUCE_APPLICATION(App)

//-------------------------------------------------------------------------------------------------//
