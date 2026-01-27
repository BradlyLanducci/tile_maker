#include <ui/components/directory_chooser.h>

//-------------------------------------------------------------------------------------------------//

DirectoryChooser::DirectoryChooser()
    : m_button("Select some shit")
    , m_chooser("Select a output directory", juce::File::getSpecialLocation(juce::File::userHomeDirectory))
{
    addAndMakeVisible(m_button);

    m_button.onClick = [this]()
    {
        m_chooser.launchAsync(juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectDirectories,
                              [this](const juce::FileChooser &fc)
                              {
                                  juce::File selectedDirectory{ fc.getResult() };
                                  m_button.setButtonText(selectedDirectory.getFileName());
                              });
    };
}

//-------------------------------------------------------------------------------------------------//

void DirectoryChooser::paint(juce::Graphics &g)
{
    g.drawText("Output Directory", getLocalBounds().removeFromTop(25), juce::Justification::left);
}

//-------------------------------------------------------------------------------------------------//

void DirectoryChooser::resized()
{
    auto bounds{ getLocalBounds() };
    m_button.setBounds(bounds.removeFromBottom(bounds.getHeight() - 25));
}

//-------------------------------------------------------------------------------------------------//
