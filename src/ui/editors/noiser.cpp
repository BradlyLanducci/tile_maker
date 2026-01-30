#include <ui/editors/noiser.h>
#include <ui/components/image_frame.h>
#include <ui/models/selectable_file_list_model.h>
#include <ui/utilities/theme.h>

#include <magic_enum/magic_enum.hpp>

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

    m_noiseTypeCombo.addItem("Value", 1);
    m_noiseTypeCombo.addItem("Perlin", 2);
    m_noiseTypeCombo.addItem("Cellular", 3);
    m_noiseTypeCombo.addItem("Simplex", 4);
    m_noiseTypeCombo.setSelectedId(1);

    m_opacitySlider.setRange(0.0, 1.0, 0.01);
    m_frequencySlider.setRange(0.0, 100.0, 0.1);
    m_seedSlider.setRange(0.0, 10'000.0, 1.0);

    auto forceUpdateCb = [this]()
    {
        juce::String selected{ getSelectedInput() };
        updateOutput(selected);
    };

    m_noiseTypeCombo.onChange = [forceUpdateCb]() { forceUpdateCb(); };
    m_opacitySlider.onValueChange = [forceUpdateCb]() { forceUpdateCb(); };
    m_frequencySlider.onValueChange = [forceUpdateCb]() { forceUpdateCb(); };
    m_seedSlider.onValueChange = [forceUpdateCb]() { forceUpdateCb(); };

    addAndMakeVisible(*mp_inputs);
    addAndMakeVisible(m_output);

    addAndMakeVisible(m_noiseTypeCombo);
    addAndMakeVisible(m_opacitySlider);
    addAndMakeVisible(m_frequencySlider);
    addAndMakeVisible(m_seedSlider);

    m_tree.addListener(this);
}

//-------------------------------------------------------------------------------------------------//

void Noiser::resized()
{
    auto bounds{ getLocalBounds() };
    int halfWidth{ bounds.getWidth() / 2 };

    auto bottom{ bounds.removeFromBottom(100) };

    int fourthWidth{ bottom.getWidth() / 4 };

    auto bottomLeft{ bottom.removeFromLeft(fourthWidth) };
    auto bottomMiddleLeft{ bottom.removeFromLeft(fourthWidth) };
    auto bottomMiddleRight{ bottom.removeFromLeft(fourthWidth) };
    auto bottomRight{ bottom };

    m_noiseTypeCombo.setBounds(bottomLeft);
    m_opacitySlider.setBounds(bottomMiddleLeft);
    m_frequencySlider.setBounds(bottomMiddleRight);
    m_seedSlider.setBounds(bottomRight);

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
        juce::String input{ treeWhosePropertyHasChanged.getType().toString() };

        updateOutput(input);
    }
}

//-------------------------------------------------------------------------------------------------//

juce::String Noiser::getSelectedInput()
{
    juce::String selected;

    juce::ValueTree inputTree{ m_tree.getChildWithName(INPUT_TREE_ID) };

    for (auto child : inputTree)
    {
        if (child.getProperty(Theme::SELECTED_KEY))
        {
            selected = child.getType().toString();
        }
    }

    return selected;
}

//-------------------------------------------------------------------------------------------------//

Noise Noiser::getSelectedNoise()
{
    int selectedId{ m_noiseTypeCombo.getSelectedId() - 1 };
    std::string selectedText{ m_noiseTypeCombo.getItemText(selectedId).toStdString() };
    std::transform(selectedText.begin(), selectedText.end(), selectedText.begin(),
                   [](auto c) { return std::toupper(c); });

    Noise::Type type{ magic_enum::enum_cast<Noise::Type>(selectedText).value() };
    float frequency{ (float)m_frequencySlider.getValue() };
    int seed{ (int)m_seedSlider.getValue() };

    return Noise{ type, frequency, seed };
}

//-------------------------------------------------------------------------------------------------//

void Noiser::updateOutput(const juce::String &input)
{
    ImageFrame *p_output{ m_output.getComponent<ImageFrame>() };

    p_output->reset();

    if (input.isNotEmpty())
    {
        ImageData inputImageData{ input.toStdString() };
        Noise noise{ getSelectedNoise() };
        float opacity{ (float)m_opacitySlider.getValue() };

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
    juce::ValueTree inputTree{ m_tree.getChildWithName(INPUT_TREE_ID) };

    Noise noise{ getSelectedNoise() };
    float opacity{ (float)m_opacitySlider.getValue() };

    for (const auto &inImage : inputTree)
    {
        ImageData inputImageData{ inImage.getType().toString().toStdString() };
        std::unique_ptr<ImageData> p_noisedImage{ ImageManipulation::applyNoise(inputImageData, noise, opacity) };
        if (p_noisedImage)
        {
            p_noisedImage->filepath = baseOutputDirectory.toStdString() + "/" + inputImageData.filename + "/";
            p_noisedImage->filename = inputImageData.filename + "_noised";

            p_noisedImage->writeToDisk();
        }
    }
}

//-------------------------------------------------------------------------------------------------//
