#include <ui/editors/noiser.h>
#include <ui/components/image_frame.h>
#include <ui/models/selectable_file_list_model.h>
#include <ui/theme/theme.h>

#include <magic_enum/magic_enum.hpp>

//-------------------------------------------------------------------------------------------------//

const juce::Identifier INPUT_TREE_ID{ "inputs" };

//-------------------------------------------------------------------------------------------------//

Noiser::Noiser()
    : m_tree("root")
    , m_output("Output", std::make_unique<ImageFrame>("Select an input"))
    , m_noiseTypeCombo("Noise Type", std::make_unique<juce::ComboBox>(), false)
    , m_opacitySlider("Opacity", std::make_unique<juce::Slider>(), false)
    , m_frequencySlider("Frequency", std::make_unique<juce::Slider>(), false)
    , m_seedSlider("Seed", std::make_unique<juce::Slider>(), false)
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

    auto p_noiseTypeCombo{ m_noiseTypeCombo.getComponent<juce::ComboBox>() };
    auto p_opacitySlider{ m_opacitySlider.getComponent<juce::Slider>() };
    auto p_frequencySlider{ m_frequencySlider.getComponent<juce::Slider>() };
    auto p_seedSlider{ m_seedSlider.getComponent<juce::Slider>() };

    p_noiseTypeCombo->addItem("Value", 1);
    p_noiseTypeCombo->addItem("Perlin", 2);
    p_noiseTypeCombo->addItem("Cellular", 3);
    p_noiseTypeCombo->addItem("Simplex", 4);
    p_noiseTypeCombo->setSelectedId(1);

    p_opacitySlider->setRange(0.0, 1.0, 0.01);
    p_frequencySlider->setRange(0.0, 100.0, 0.1);
    p_seedSlider->setRange(0.0, 10'000.0, 1.0);

    auto forceUpdateCb{ [this]()
                        {
                            juce::String selected{ getSelectedInput() };
                            updateOutput(selected);
                        } };

    p_noiseTypeCombo->onChange = [forceUpdateCb]() { forceUpdateCb(); };
    p_opacitySlider->onValueChange = [forceUpdateCb]() { forceUpdateCb(); };
    p_frequencySlider->onValueChange = [forceUpdateCb]() { forceUpdateCb(); };
    p_seedSlider->onValueChange = [forceUpdateCb]() { forceUpdateCb(); };

    m_noiseTypeCombo.setLookAndFeel(&m_look);
    m_opacitySlider.setLookAndFeel(&m_look);
    m_frequencySlider.setLookAndFeel(&m_look);
    m_seedSlider.setLookAndFeel(&m_look);

    addAndMakeVisible(*mp_inputs);
    addAndMakeVisible(m_output);

    addAndMakeVisible(m_noiseTypeCombo);
    addAndMakeVisible(m_opacitySlider);
    addAndMakeVisible(m_frequencySlider);
    addAndMakeVisible(m_seedSlider);

    m_tree.addListener(this);
}

//-------------------------------------------------------------------------------------------------//

Noiser::~Noiser()
{
    m_noiseTypeCombo.setLookAndFeel(nullptr);
    m_opacitySlider.setLookAndFeel(nullptr);
    m_frequencySlider.setLookAndFeel(nullptr);
    m_seedSlider.setLookAndFeel(nullptr);
}

//-------------------------------------------------------------------------------------------------//

void Noiser::resized()
{
    auto bounds{ getLocalBounds() };
    int thirdWidth{ bounds.getWidth() / 3 };

    auto left{ bounds.removeFromLeft(thirdWidth) };
    auto middle{ bounds.removeFromLeft(thirdWidth) };
    auto right{ bounds };

    left.reduce(Theme::DEFAULT_PADDING, Theme::DEFAULT_PADDING);

    middle.reduce(Theme::DEFAULT_PADDING, Theme::DEFAULT_PADDING);
    right.reduce(Theme::DEFAULT_PADDING, Theme::DEFAULT_PADDING);

    int sideLength{ std::min(std::min(left.getWidth(), left.getHeight()), 400) };
    sideLength -= Theme::DEFAULT_PADDING;

    auto centerX{ (left.getWidth() - sideLength) / 2 };

    const int optionHeight{ 75 };
    left.removeFromLeft(100);
    m_noiseTypeCombo.setBounds(left.removeFromTop(optionHeight));
    m_opacitySlider.setBounds(left.removeFromTop(optionHeight));
    m_frequencySlider.setBounds(left.removeFromTop(optionHeight));
    m_seedSlider.setBounds(left.withHeight(optionHeight));

    mp_inputs->setBounds(middle.getX() + centerX, 0, sideLength, sideLength);
    m_output.setBounds(right.getX() + centerX, 0, sideLength, sideLength);
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
    auto p_noiseTypeCombo{ m_noiseTypeCombo.getComponent<juce::ComboBox>() };
    auto p_frequencySlider{ m_frequencySlider.getComponent<juce::Slider>() };
    auto p_seedSlider{ m_seedSlider.getComponent<juce::Slider>() };

    int selectedId{ p_noiseTypeCombo->getSelectedId() - 1 };
    std::string selectedText{ p_noiseTypeCombo->getItemText(selectedId).toStdString() };
    std::transform(selectedText.begin(), selectedText.end(), selectedText.begin(),
                   [](auto c) { return std::toupper(c); });

    Noise::Type type{ magic_enum::enum_cast<Noise::Type>(selectedText).value() };
    float frequency{ (float)p_frequencySlider->getValue() };
    int seed{ (int)p_seedSlider->getValue() };

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

        auto p_opacitySlider{ m_opacitySlider.getComponent<juce::Slider>() };
        float opacity{ (float)p_opacitySlider->getValue() };

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

    auto p_opacitySlider{ m_opacitySlider.getComponent<juce::Slider>() };
    float opacity{ (float)p_opacitySlider->getValue() };

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
