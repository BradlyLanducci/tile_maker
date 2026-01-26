#pragma once

#include <ui/file_list.h>

#include <juce_gui_basics/juce_gui_basics.h>

//-------------------------------------------------------------------------------------------------//

class ImageListContainer : public juce::Component
{
public:
    ImageListContainer(const juce::StringArray &images);

    void resized() override;

private:
    FileListModel m_model;
    FileList m_list;
};

//-------------------------------------------------------------------------------------------------//
