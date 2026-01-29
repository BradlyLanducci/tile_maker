#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

//-------------------------------------------------------------------------------------------------//

class SelectableFileListModel final : public juce::ListBoxModel
{
public:
    explicit SelectableFileListModel(juce::ValueTree tree);

    int getNumRows() override;

    void paintListBoxItem(int rowNumber, juce::Graphics &g, int width, int height, bool rowIsSelected) override;

private:
    juce::ValueTree m_tree;
};

//-------------------------------------------------------------------------------------------------//
