#include <ui/editors/blender.h>
#include <processing/image_manipulation.h>
#include <ui/components/image_frame.h>
#include <ui/models/mapped_file_list_model.h>
#include <ui/models/file_list_model.h>
#include <ui/components/image_list.h>
#include <ui/utilities/theme.h>

//-------------------------------------------------------------------------------------------------//

Blender::Blender()
    : m_tree("root")
    , m_output("Output", std::make_unique<ImageFrame>())
{
    juce::ValueTree inputTree{ "Inputs" };
    juce::ValueTree templatesTree{ "Templates" };

    m_tree.appendChild(inputTree, nullptr);
    m_tree.appendChild(templatesTree, nullptr);

    mp_inputs = std::make_unique<TitledComponent>(
        "Inputs", std::make_unique<ImageDropView>(inputTree, [this](juce::Component *p_caller, juce::ValueTree tree)
                                                  { return dropViewChanged(p_caller, tree); }));

    mp_templates = std::make_unique<TitledComponent>(
        "Templates",
        std::make_unique<ImageDropView>(templatesTree, [this](juce::Component *p_caller, juce::ValueTree tree)
                                        { return dropViewChanged(p_caller, tree); }));

    addAndMakeVisible(*mp_inputs);
    addAndMakeVisible(*mp_templates);
    addAndMakeVisible(m_output);

    m_tree.addListener(this);
}

//-------------------------------------------------------------------------------------------------//

std::unique_ptr<juce::Component> Blender::dropViewChanged(juce::Component *p_caller, juce::ValueTree tree)
{
    std::unique_ptr<juce::Component> p_imageDisplayer{ nullptr };

    auto parent{ p_caller->getParentComponent() };
    if (parent == mp_inputs.get())
    {
        p_imageDisplayer = std::make_unique<ImageList<MappedFileListModel>>(tree);
    }
    else
    {
        p_imageDisplayer = std::make_unique<ImageList<FileListModel>>(tree);
    }

    return std::move(p_imageDisplayer);
}

//-------------------------------------------------------------------------------------------------//

void Blender::valueTreePropertyChanged(juce::ValueTree &treeWhosePropertyHasChanged, const juce::Identifier &property)
{
    (void)treeWhosePropertyHasChanged;
    (void)property;

    juce::ValueTree inputTree{ m_tree.getChildWithName("Inputs") };
    juce::ValueTree templatesTree{ m_tree.getChildWithName("Templates") };

    if (inputTree.getNumChildren() == 0 || templatesTree.getNumChildren() == 0)
    {
        return;
    }

    ImageFrame *p_output{ m_output.getComponent<ImageFrame>() };

    p_output->reset();

    std::vector<ColourMappedImageData> mappedImageData;

    for (const auto &inImage : inputTree)
    {
        juce::Colour inColor{ juce::Colour::fromString(
            inImage.getProperty(Theme::COLOUR_KEY, juce::Colours::black.toString()).toString()) };
        juce::String inFile{ inImage.getType().toString() };
        mappedImageData.emplace_back(inColor, std::make_unique<ImageData>(inFile.toStdString()));
    }

    for (const auto &templateImage : templatesTree)
    {
        juce::String templateFile{ templateImage.getType().toString() };
        ImageData templateImageData{ templateFile.toStdString() };
        std::unique_ptr<ImageData> p_out{ ImageManipulation::blendInputsWithTemplate(mappedImageData,
                                                                                     templateImageData) };

        // This should be changed to just effect the selected image
        if (p_out)
        {
            p_output->setImage(std::move(p_out));
        }
    }
}

//-------------------------------------------------------------------------------------------------//

void Blender::resized()
{
    auto bounds{ getLocalBounds() };
    int thirdWidth{ bounds.getWidth() / 3 };

    auto left{ bounds.removeFromLeft(thirdWidth) };
    auto middle{ bounds.removeFromLeft(thirdWidth) };
    auto right{ bounds };

    const int padding{ 4 };
    left.reduce(padding, padding);
    middle.reduce(padding, padding);
    right.reduce(padding, padding);

    left.setHeight(std::min(left.getWidth(), left.getHeight()));
    middle.setHeight(std::min(middle.getWidth(), middle.getHeight()));
    right.setHeight(std::min(right.getWidth(), right.getHeight()));

    int sideLength{ std::min(left.getWidth(), left.getHeight()) };

    int centeredHeight{ (bounds.getHeight() - sideLength) / 2 };
    mp_inputs->setBounds(left.getX(), centeredHeight, sideLength, sideLength);
    mp_templates->setBounds(middle.getX(), centeredHeight, sideLength, sideLength);
    m_output.setBounds(right.getX(), centeredHeight, sideLength, sideLength);
}

//-------------------------------------------------------------------------------------------------//

void Blender::generate(const juce::String &baseOutputDirectory)
{
    juce::ValueTree inputTree{ m_tree.getChildWithName("Inputs") };
    juce::ValueTree templatesTree{ m_tree.getChildWithName("Templates") };

    ImageFrame *p_output{ m_output.getComponent<ImageFrame>() };

    p_output->reset();

    std::vector<ColourMappedImageData> mappedImageData;

    for (const auto &inImage : inputTree)
    {
        juce::Colour inColor{ juce::Colour::fromString(
            inImage.getProperty(Theme::COLOUR_KEY, juce::Colours::black.toString()).toString()) };
        juce::String inFile{ inImage.getType().toString() };
        mappedImageData.emplace_back(inColor, std::make_unique<ImageData>(inFile.toStdString()));
    }

    uint32_t i{};
    for (const auto &templateImage : templatesTree)
    {
        juce::String templateFile{ templateImage.getType().toString() };
        ImageData templateImageData{ templateFile.toStdString() };
        std::unique_ptr<ImageData> p_blendedImage{ ImageManipulation::blendInputsWithTemplate(mappedImageData,
                                                                                              templateImageData) };

        if (p_blendedImage)
        {
            p_blendedImage->filepath = baseOutputDirectory.toStdString() + "/" + templateImageData.filename + "/";
            p_blendedImage->filename = templateImageData.filename + "_blended_" + std::to_string(i);

            p_blendedImage->writeToDisk();

            i++;
        }
    }
}

//-------------------------------------------------------------------------------------------------//
