#include <ui/models/mapped_file_list_model.h>
#include <ui/components/image_color_picker.h>

//-------------------------------------------------------------------------------------------------//

MappedFileListModel::MappedFileListModel(const juce::StringArray &images)
    : m_images(images)
{
}

//-------------------------------------------------------------------------------------------------//

int MappedFileListModel::getNumRows()
{
    return m_images.size();
}

//-------------------------------------------------------------------------------------------------//

void MappedFileListModel::paintListBoxItem(int rowNumber, juce::Graphics &g, int width, int height, bool rowIsSelected)
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

juce::Component *MappedFileListModel::refreshComponentForRow(int rowNumber, bool isRowSelected,
                                                             juce::Component *p_existingComponentToUpdate)
{
    (void)(isRowSelected);

    if (!p_existingComponentToUpdate)
    {
        // This should be impossible
        jassert(m_images.size() >= 2);

        uint8_t numColours{ static_cast<uint8_t>(m_images.size() - 1) };
        uint8_t colourStep{ static_cast<uint8_t>(0xFF / numColours) };
        uint8_t colourValue{ static_cast<uint8_t>(rowNumber * colourStep) };
        juce::Colour defaultColour{ colourValue, colourValue, colourValue };
        // Greyscale
        p_existingComponentToUpdate = new ImageColorPicker(m_images[rowNumber], defaultColour);
    }

    return p_existingComponentToUpdate;
}

//-------------------------------------------------------------------------------------------------//
