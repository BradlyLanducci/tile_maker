#pragma once

#include <ui/models/file_list_model.h>

#include <juce_gui_basics/juce_gui_basics.h>

//-------------------------------------------------------------------------------------------------//

class ImageList : public juce::Component
{
public:
    ImageList(const juce::StringArray &images);

    void resized() override;

private:
    FileListModel m_model;
    juce::ListBox m_list;
};

//-------------------------------------------------------------------------------------------------//
