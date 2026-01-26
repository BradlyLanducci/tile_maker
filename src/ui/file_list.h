#pragma once

#include <ui/file_list_model.h>

#include <juce_gui_basics/juce_gui_basics.h>

//-------------------------------------------------------------------------------------------------//

class FileList : public juce::ListBox
{
public:
    FileList(FileListModel &model);
};

//-------------------------------------------------------------------------------------------------//
