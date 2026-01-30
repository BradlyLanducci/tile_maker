#include <ui/editors/noiser.h>
#include <ui/components/image_frame.h>
#include <ui/models/selectable_file_list_model.h>
#include <ui/utilities/theme.h>
#include <processing/image_manipulation.h>

//-------------------------------------------------------------------------------------------------//

const juce::Identifier INPUT_TREE_ID{ "inputs" };

//-------------------------------------------------------------------------------------------------//

Noiser::Noiser()
    : m_tree("root")
    , m_output("Output", std::make_unique<ImageFrame>("Select an input"))
{
    juce::ValueTree inputTree{ INPUT_TREE_ID };

    m_tree.appendChild(inputTree, nullptr);

    mp_inputs = std::make_unique<TitledComponent>(
        "Inputs", std::make_unique<ImageDropView>(inputTree,
                                                  [this](juce::Component *p_caller, juce::ValueTree tree)
                                                  {
                                                      (void)p_caller;
                                                      return dropViewChanged(tree);
                                                  }));
    addAndMakeVisible(*mp_inputs);
    addAndMakeVisible(m_output);

    m_tree.addListener(this);
}

//-------------------------------------------------------------------------------------------------//

void Noiser::resized()
{
    auto bounds{ getLocalBounds() };
    int halfWidth{ bounds.getWidth() / 2 };

    auto left{ bounds.removeFromLeft(halfWidth) };
    auto right{ bounds };

    const int padding{ 4 };
    left.reduce(padding, padding);
    right.reduce(padding, padding);

    left.setHeight(std::min(left.getWidth(), left.getHeight()));
    right.setHeight(std::min(right.getWidth(), right.getHeight()));

    int sideLength{ std::min(left.getWidth(), left.getHeight()) };

    int centeredHeight{ (bounds.getHeight() - sideLength) / 2 };
    mp_inputs->setBounds(left.getX(), centeredHeight, sideLength, sideLength);
    m_output.setBounds(right.getX(), centeredHeight, sideLength, sideLength);
}

//-------------------------------------------------------------------------------------------------//

std::unique_ptr<juce::Component> Noiser::dropViewChanged(juce::ValueTree tree)
{
    return std::make_unique<ImageList>(std::make_unique<SelectableFileListModel>(tree));
}

//-------------------------------------------------------------------------------------------------//

void Noiser::valueTreePropertyChanged(juce::ValueTree &treeWhosePropertyHasChanged, const juce::Identifier &property)
{
    if (property == Theme::SELECTED_KEY && treeWhosePropertyHasChanged[property])
    {
        juce::String inputFilename{ treeWhosePropertyHasChanged.getType().toString() };

        ImageFrame *p_output{ m_output.getComponent<ImageFrame>() };

        p_output->reset();
        ImageData inputImageData{ inputFilename.toStdString() };

        /// TODO: These should be configurable through UI
        float opacity{ 0.25f };
        Noise::Type type{ Noise::Type::VALUE };
        float frequency{ 50.f };
        int seed{ 0 };

        Noise noise{ type, frequency, seed };

        std::unique_ptr<ImageData> p_noisedImage{ ImageManipulation::applyNoise(inputImageData, noise, opacity) };
        if (p_noisedImage)
        {
            p_output->setImage(std::move(p_noisedImage));
        }
    }
}

//-------------------------------------------------------------------------------------------------//

void Noiser::generate(const juce::String &baseOutputDirectory)
{
    (void)baseOutputDirectory;
}

//-------------------------------------------------------------------------------------------------//
