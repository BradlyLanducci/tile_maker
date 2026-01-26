#include <ui/masker.h>

#include <image/image_manipulation.h>
#include <ui/image_frame.h>

//-------------------------------------------------------------------------------------------------//

Masker::Masker()
    : m_input("Input", new ImageDropView([this]() { imagesUpdated(); }))
    , m_mask("Mask", new ImageDropView([this]() { imagesUpdated(); }))
    , m_output("Output", new ImageFrame())
{
    addAndMakeVisible(m_input);
    addAndMakeVisible(m_mask);
    addAndMakeVisible(m_output);
}

//-------------------------------------------------------------------------------------------------//

void Masker::imagesUpdated()
{
    juce::StringArray inImages{ static_cast<ImageDropView *>(m_input.getComponent())->getImages() };
    juce::StringArray maskImages{ static_cast<ImageDropView *>(m_mask.getComponent())->getImages() };

    ImageFrame *p_output{ static_cast<ImageFrame *>(m_output.getComponent()) };
    if (inImages.isEmpty() || maskImages.isEmpty())
    {
        p_output->reset();
        return;
    }

    for (const auto &inImage : inImages)
    {
        for (const auto &maskImage : maskImages)
        {
            ImageData in{ inImage.toStdString() };
            ImageData mask{ maskImage.toStdString() };
            std::unique_ptr<ImageData> out{ ImageManipulation::createMaskedImage(in, mask) };
            p_output->setImage(std::move(out));
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
    m_input.setBounds(left.getX(), centeredHeight, sideLength, sideLength);
    m_mask.setBounds(middle.getX(), centeredHeight, sideLength, sideLength);
    m_output.setBounds(right.getX(), centeredHeight, sideLength, sideLength);
}

//-------------------------------------------------------------------------------------------------//
