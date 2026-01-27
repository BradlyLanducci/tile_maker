#include <ui/models/file_list_model.h>
#include <ui/utilities/theme.h>

//-------------------------------------------------------------------------------------------------//

FileListModel::FileListModel(juce::ValueTree tree)
    : m_tree(tree)
{
}

//-------------------------------------------------------------------------------------------------//

int FileListModel::getNumRows()
{
    return m_tree.getNumChildren();
}

//-------------------------------------------------------------------------------------------------//

void FileListModel::paintListBoxItem(int rowNumber, juce::Graphics &g, int width, int height, bool rowIsSelected)
{
    (void)rowIsSelected;

    g.fillAll(juce::Colours::transparentBlack);

    if (rowNumber < getNumRows())
    {
        juce::ValueTree child{ m_tree.getChild(rowNumber) };
        juce::File file{ child.getType().toString() };
        juce::String fileName{ file.getFileNameWithoutExtension().replace("_", " ") };
        g.drawText(fileName, 0, 0, width, height, juce::Justification::left);
        if (child.isValid())
        {
            child.setProperty(Theme::FORCE_UPDATE, Theme::FORCE_UPDATE.toString(), nullptr);
        }
    }
}

//-------------------------------------------------------------------------------------------------//
