#include <ui/editors/masker.h>
#include <processing/image_manipulation.h>
#include <ui/components/image_frame.h>
#include <ui/models/file_list_model.h>
#include <ui/components/image_list.h>

//-------------------------------------------------------------------------------------------------//

Masker::Masker()
    : m_tree{ "root" }
    , m_output("Output", new ImageFrame())
{
    juce::ValueTree inputTree{ "Inputs" };
    juce::ValueTree maskTree{ "Masks" };

    m_tree.appendChild(inputTree, nullptr);
    m_tree.appendChild(maskTree, nullptr);

    mp_input = std::make_unique<TitledComponent>(
        "Inputs", new ImageDropView(inputTree,
                                    [this](juce::Component *p_caller, juce::ValueTree tree)
                                    {
                                        (void)p_caller;
                                        return imagesUpdated(tree);
                                    }));
    mp_mask = std::make_unique<TitledComponent>(
        "Masks", new ImageDropView(maskTree,
                                   [this](juce::Component *p_caller, juce::ValueTree tree)
                                   {
                                       (void)p_caller;
                                       return imagesUpdated(tree);
                                   }));

    addAndMakeVisible(*mp_input);
    addAndMakeVisible(*mp_mask);
    addAndMakeVisible(m_output);
}

//-------------------------------------------------------------------------------------------------//

std::unique_ptr<juce::Component> Masker::imagesUpdated(juce::ValueTree tree)
{
    juce::ValueTree inputTree{ m_tree.getChildWithName("Inputs") };
    juce::ValueTree maskTree{ m_tree.getChildWithName("Masks") };

    ImageFrame *p_output{ m_output.getComponent<ImageFrame>() };

    p_output->reset();

    for (const auto &inImage : inputTree)
    {
        for (const auto &maskImage : maskTree)
        {
            ImageData in{ inImage.getType().toString().toStdString() };
            ImageData mask{ maskImage.getType().toString().toStdString() };
            std::unique_ptr<ImageData> p_maskedImage{ ImageManipulation::createMaskedImage(in, mask) };
            if (p_maskedImage)
            {
                p_output->setImage(std::move(p_maskedImage));
                break; // REMOVE THIS IT'S SHOULD ONLY DO FOR THE SELECTED IMAGES (not implemented yet)
            }
        }
    }

    return std::make_unique<ImageList<FileListModel>>(tree);
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
    juce::ValueTree inputTree{ m_tree.getChildWithName("Inputs") };
    juce::ValueTree maskTree{ m_tree.getChildWithName("Masks") };

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
