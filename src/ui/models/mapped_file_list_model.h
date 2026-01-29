#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

//-------------------------------------------------------------------------------------------------//

class MappedFileListModel final : public juce::ListBoxModel
{
public:
    MappedFileListModel(juce::ValueTree tree);

    int getNumRows() override;

    void paintListBoxItem(int rowNumber, juce::Graphics &g, int width, int height, bool rowIsSelected) override;
    juce::Component *refreshComponentForRow(int rowNumber, bool isRowSelected,
                                            juce::Component *p_existingComponentToUpdate) override;

private:
    juce::ValueTree m_tree;
};

//-------------------------------------------------------------------------------------------------//
