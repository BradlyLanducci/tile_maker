#include <ui/main_window.h>
#include <ui/theme/theme.h>
#include <BinaryData.h>

//-------------------------------------------------------------------------------------------------//

MainWindow::MainWindow(juce::String name)
    : DocumentWindow(name, juce::Colours::lightgrey, DocumentWindow::closeButton | DocumentWindow::minimiseButton)
{
    setVisible(true);

    setContentOwned(&m_content, true);
    m_content.setBounds(0, 0, 1440, 810);

    auto font{ juce::Typeface::createSystemTypefaceFor(BinaryData::m5x7_ttf, BinaryData::m5x7_ttfSize) };
    juce::LookAndFeel::getDefaultLookAndFeel().setDefaultSansSerifTypeface(font);
    setLookAndFeel(&m_look);
}

//-------------------------------------------------------------------------------------------------//

MainWindow::~MainWindow()
{
    setLookAndFeel(nullptr);
}

//-------------------------------------------------------------------------------------------------//

void MainWindow::closeButtonPressed()
{
    juce::JUCEApplication::getInstance()->systemRequestedQuit();
}

//-------------------------------------------------------------------------------------------------//
