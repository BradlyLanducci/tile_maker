#include <ui/models/mapped_file_list_model.h>
#include <ui/components/image_color_picker.h>
#include <ui/theme/theme.h>

//-------------------------------------------------------------------------------------------------//

MappedFileListModel::MappedFileListModel(juce::ValueTree tree)
    : m_tree(tree)
{
}

//-------------------------------------------------------------------------------------------------//

int MappedFileListModel::getNumRows()
{
    return m_tree.getNumChildren();
}

//-------------------------------------------------------------------------------------------------//

void MappedFileListModel::paintListBoxItem(int rowNumber, juce::Graphics &g, int width, int height, bool rowIsSelected)
{
    (void)rowIsSelected;

    g.fillAll(juce::Colours::transparentBlack);

    if (rowNumber < getNumRows())
    {
        juce::ValueTree child{ m_tree.getChild(rowNumber) };
        juce::File file{ child.getType().toString() };
        juce::String fileName{ file.getFileNameWithoutExtension().replace("_", " ") };
        g.setFont(Theme::NORMAL_FONT_SIZE);
        g.setColour(Theme::LIGHT_TEXT);
        g.drawText(fileName, 10, 0, width, height, juce::Justification::left);
    }
}

//-------------------------------------------------------------------------------------------------//

juce::Component *MappedFileListModel::refreshComponentForRow(int rowNumber, bool isRowSelected,
                                                             juce::Component *p_existingComponentToUpdate)
{
    (void)(isRowSelected);

    if (!p_existingComponentToUpdate)
    {
        uint8_t numColours{ static_cast<uint8_t>(getNumRows() == 1 ? 1 : getNumRows() - 1) };
        uint8_t colourStep{ static_cast<uint8_t>(0xFF / numColours) };
        uint8_t colourValue{ static_cast<uint8_t>(rowNumber * colourStep) };
        juce::Colour defaultColour{ colourValue, colourValue, colourValue };
        // Greyscale
        juce::ValueTree child{ m_tree.getChild(rowNumber) };

        if (child.isValid())
        {
            juce::String fileName{ child.getType().toString() };
            child.setProperty(Theme::COLOUR_KEY, defaultColour.toString(), nullptr);

            p_existingComponentToUpdate = new ImageColorPicker(child);
        }
    }

    return p_existingComponentToUpdate;
}

//-------------------------------------------------------------------------------------------------//
