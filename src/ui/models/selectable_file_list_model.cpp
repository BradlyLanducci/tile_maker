#include <ui/models/selectable_file_list_model.h>
#include <ui/theme/theme.h>

//-------------------------------------------------------------------------------------------------//

SelectableFileListModel::SelectableFileListModel(juce::ValueTree tree)
    : m_tree(tree)
{
}

//-------------------------------------------------------------------------------------------------//

int SelectableFileListModel::getNumRows()
{
    return m_tree.getNumChildren();
}

//-------------------------------------------------------------------------------------------------//

void SelectableFileListModel::paintListBoxItem(int rowNumber, juce::Graphics &g, int width, int height,
                                               bool rowIsSelected)
{
    if (rowNumber < getNumRows())
    {
        juce::ValueTree child{ m_tree.getChild(rowNumber) };
        juce::File file{ child.getType().toString() };
        juce::String fileName{ file.getFileNameWithoutExtension().replace("_", " ") };

        if (rowIsSelected)
        {
            g.fillAll(Theme::LIGHT_TEXT);
            child.setProperty(Theme::SELECTED_KEY, true, nullptr);
            g.setColour(Theme::DARK_TEXT);
        }
        else
        {
            g.fillAll(juce::Colours::transparentBlack);
            child.setProperty(Theme::SELECTED_KEY, false, nullptr);
            g.setColour(Theme::LIGHT_TEXT);
        }

        g.setFont(Theme::NORMAL_FONT_SIZE);
        g.drawText(fileName, Theme::DEFAULT_PADDING, 0, width, height, juce::Justification::left);

        if (child.isValid())
        {
            child.setProperty(Theme::FORCE_UPDATE, Theme::FORCE_UPDATE.toString(), nullptr);
        }
    }
}

//-------------------------------------------------------------------------------------------------//
