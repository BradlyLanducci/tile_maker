#include <ui/app.h>

//-------------------------------------------------------------------------------------------------//

void App::initialise(const juce::String &commandLine)
{
    (void)commandLine;
    mp_window.reset(new MainWindow("Tile Maker"));
    mp_window->setVisible(true);
}

//-------------------------------------------------------------------------------------------------//

void App::shutdown()
{
    mp_window = nullptr;
}

//-------------------------------------------------------------------------------------------------//

const juce::String App::getApplicationName()
{
    return "Tile Maker";
}

//-------------------------------------------------------------------------------------------------//

const juce::String App::getApplicationVersion()
{
    return "1.0";
}

//-------------------------------------------------------------------------------------------------//
