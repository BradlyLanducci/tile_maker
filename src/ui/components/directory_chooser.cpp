#include <ui/components/directory_chooser.h>
#include <ui/theme/theme.h>

//-------------------------------------------------------------------------------------------------//

DirectoryChooser::DirectoryChooser()
    : m_button(juce::File::getSpecialLocation(juce::File::userDocumentsDirectory).getFileName())
    , m_chooser("What is this", juce::File::getSpecialLocation(juce::File::userDocumentsDirectory))
{
    addAndMakeVisible(m_button);

    m_button.onClick = [this]()
    {
        m_chooser.launchAsync(juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectDirectories,
                              [this](const juce::FileChooser &fc)
                              {
                                  juce::File selectedDirectory{ fc.getResult() };
                                  if (selectedDirectory.exists())
                                  {
                                      m_selectedDirectory = selectedDirectory.getFullPathName();
                                      m_button.setButtonText(selectedDirectory.getFileName());
                                  }
                              });
    };
}

//-------------------------------------------------------------------------------------------------//

void DirectoryChooser::paint(juce::Graphics &g)
{
    g.setColour(Theme::LIGHT_TEXT);
    g.setFont(Theme::NORMAL_FONT_SIZE);
    g.drawText("Output Directory", getLocalBounds().removeFromTop(25), juce::Justification::centred);
}

//-------------------------------------------------------------------------------------------------//

void DirectoryChooser::resized()
{
    auto bounds{ getLocalBounds() };
    m_button.setBounds(bounds.removeFromBottom(bounds.getHeight() - 25));
}
//-------------------------------------------------------------------------------------------------//

juce::String DirectoryChooser::getOutputDirectory() const
{
    return m_selectedDirectory;
}

//-------------------------------------------------------------------------------------------------//
