#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

//-------------------------------------------------------------------------------------------------//

class FileListModel : public juce::ListBoxModel
{
public:
    FileListModel(juce::ValueTree tree);

    int getNumRows() override;
    void paintListBoxItem(int rowNumber, juce::Graphics &g, int width, int height, bool rowIsSelected) override;

private:
    void getFilenameFromPath();
    juce::ValueTree m_tree;
};

//-------------------------------------------------------------------------------------------------//
