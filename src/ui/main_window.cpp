#include <ui/main_window.h>

//-------------------------------------------------------------------------------------------------//

MainWindow::MainWindow(juce::String name)
    : DocumentWindow(name, juce::Colours::lightgrey, DocumentWindow::allButtons)
{
    setVisible(true);

    setContentOwned(&m_content, true);
    setResizable(true, true);
    getConstrainer()->setFixedAspectRatio(16.0 / 9.0);
    setResizeLimits(1920 / 4, 1080 / 4, 1920 * 2, 1080 * 2);

    m_content.setBounds(0, 0, 1440, 810);
}

//-------------------------------------------------------------------------------------------------//

void MainWindow::closeButtonPressed()
{
    juce::JUCEApplication::getInstance()->systemRequestedQuit();
}

//-------------------------------------------------------------------------------------------------//
