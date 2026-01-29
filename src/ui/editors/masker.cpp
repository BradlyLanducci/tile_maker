#include <ui/editors/masker.h>
#include <processing/image_manipulation.h>
#include <ui/components/image_frame.h>
#include <ui/models/selectable_file_list_model.h>
#include <ui/components/image_list.h>
#include <ui/utilities/theme.h>

//-------------------------------------------------------------------------------------------------//

const juce::Identifier INPUT_TREE_ID{ "inputs" };
const juce::Identifier MASK_TREE_ID{ "masks" };

//-------------------------------------------------------------------------------------------------//

Masker::Masker()
    : m_tree{ "root" }
    , m_output("Output", std::make_unique<ImageFrame>("Select an input and mask"))
{
    juce::ValueTree inputTree{ INPUT_TREE_ID };
    juce::ValueTree maskTree{ MASK_TREE_ID };

    m_tree.appendChild(inputTree, nullptr);
    m_tree.appendChild(maskTree, nullptr);

    mp_input = std::make_unique<TitledComponent>(
        "Inputs", std::make_unique<ImageDropView>(inputTree,
                                                  [this](juce::Component *p_caller, juce::ValueTree tree)
                                                  {
                                                      (void)p_caller;
                                                      return dropViewChanged(tree);
                                                  }));
    mp_mask = std::make_unique<TitledComponent>(
        "Masks", std::make_unique<ImageDropView>(maskTree,
                                                 [this](juce::Component *p_caller, juce::ValueTree tree)
                                                 {
                                                     (void)p_caller;
                                                     return dropViewChanged(tree);
                                                 }));

    addAndMakeVisible(*mp_input);
    addAndMakeVisible(*mp_mask);
    addAndMakeVisible(m_output);

    m_tree.addListener(this);
}

//-------------------------------------------------------------------------------------------------//

std::unique_ptr<juce::Component> Masker::dropViewChanged(juce::ValueTree tree)
{
    ImageFrame *p_output{ m_output.getComponent<ImageFrame>() };

    p_output->reset();

    std::unique_ptr<SelectableFileListModel> p_model{ std::make_unique<SelectableFileListModel>(tree) };

    return std::make_unique<ImageList>(std::move(p_model));
}

//-------------------------------------------------------------------------------------------------//

juce::String Masker::getSelectedFile(const juce::ValueTree &tree)
{
    for (auto child : tree)
    {
        bool selected{ child.getProperty(Theme::SELECTED_KEY, false) };
        if (selected)
        {
            return child.getType().toString();
        }
    }
    return "";
}

//-------------------------------------------------------------------------------------------------//

void Masker::valueTreePropertyChanged(juce::ValueTree &treeWhosePropertyHasChanged, const juce::Identifier &property)
{
    juce::ValueTree parent{ treeWhosePropertyHasChanged.getParent() };
    if (parent.isValid())
    {
        auto parentId{ parent.getType() };
        if (property == Theme::SELECTED_KEY && treeWhosePropertyHasChanged[property])
        {
            juce::String selectedInput;
            juce::String selectedMask;

            if (parentId == INPUT_TREE_ID)
            {
                selectedInput = treeWhosePropertyHasChanged.getType().toString();

                juce::ValueTree maskTree{ m_tree.getChildWithName(MASK_TREE_ID) };
                selectedMask = getSelectedFile(maskTree);
            }
            else if (parentId == MASK_TREE_ID)
            {
                juce::ValueTree inputTree{ m_tree.getChildWithName(INPUT_TREE_ID) };
                selectedInput = getSelectedFile(inputTree);

                selectedMask = treeWhosePropertyHasChanged.getType().toString();
            }

            if (!selectedInput.isEmpty() && !selectedMask.isEmpty())
            {
                ImageFrame *p_output{ m_output.getComponent<ImageFrame>() };

                p_output->reset();

                ImageData in{ selectedInput.toStdString() };
                ImageData mask{ selectedMask.toStdString() };
                std::unique_ptr<ImageData> p_maskedImage{ ImageManipulation::createMaskedImage(in, mask) };

                p_output->setImage(std::move(p_maskedImage));
            }
        }
    }
}

//-------------------------------------------------------------------------------------------------//

void Masker::resized()
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
    mp_input->setBounds(left.getX(), centeredHeight, sideLength, sideLength);
    mp_mask->setBounds(middle.getX(), centeredHeight, sideLength, sideLength);
    m_output.setBounds(right.getX(), centeredHeight, sideLength, sideLength);
}

//-------------------------------------------------------------------------------------------------//

void Masker::generate(const juce::String &baseOutputDirectory)
{
    juce::ValueTree inputTree{ m_tree.getChildWithName(INPUT_TREE_ID) };
    juce::ValueTree maskTree{ m_tree.getChildWithName(MASK_TREE_ID) };

    for (const auto &inImage : inputTree)
    {
        for (const auto &maskImage : maskTree)
        {
            ImageData in{ inImage.getType().toString().toStdString() };
            ImageData mask{ maskImage.getType().toString().toStdString() };
            std::unique_ptr<ImageData> p_maskedImage{ ImageManipulation::createMaskedImage(in, mask) };
            if (p_maskedImage)
            {
                p_maskedImage->filepath = baseOutputDirectory.toStdString() + "/" + in.filename + "/";
                p_maskedImage->filename = in.filename + "_" + mask.filename + "_masked";

                p_maskedImage->writeToDisk();
            }
        }
    }
}

//-------------------------------------------------------------------------------------------------//
