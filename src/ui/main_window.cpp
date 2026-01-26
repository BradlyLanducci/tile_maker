#include <ui/main_window.h>

//-------------------------------------------------------------------------------------------------//

MainWindow::MainWindow(juce::String name)
    : DocumentWindow(name, juce::Colours::lightgrey, DocumentWindow::allButtons)
{
    centreWithSize(300, 200);
    setVisible(true);

    setContentOwned(&m_masker, true);
}

//-------------------------------------------------------------------------------------------------//

void MainWindow::closeButtonPressed()
{
    juce::JUCEApplication::getInstance()->systemRequestedQuit();
}

//-------------------------------------------------------------------------------------------------//
