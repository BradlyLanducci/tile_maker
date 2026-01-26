#include <ui/file_list_model.h>

//-------------------------------------------------------------------------------------------------//

FileListModel::FileListModel(const juce::StringArray &images)
    : m_images(images)
{
}

//-------------------------------------------------------------------------------------------------//

int FileListModel::getNumRows()
{
    return m_images.size();
}

//-------------------------------------------------------------------------------------------------//

void FileListModel::paintListBoxItem(int rowNumber, juce::Graphics &g, int width, int height, bool rowIsSelected)
{
    (void)rowIsSelected;

    g.fillAll(juce::Colours::transparentBlack);

    if (rowNumber < m_images.size())
    {
        juce::File file{ m_images[rowNumber] };
        juce::String fileName{ file.getFileNameWithoutExtension().replace("_", " ") };
        g.drawText(fileName, 0, 0, width, height, juce::Justification::left);
    }
}

//-------------------------------------------------------------------------------------------------//
