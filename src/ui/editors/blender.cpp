#include <ui/editors/blender.h>
#include <processing/image_manipulation.h>
#include <ui/components/image_frame.h>
#include <ui/models/mapped_file_list_model.h>
#include <ui/models/file_list_model.h>
#include <ui/components/image_list.h>

//-------------------------------------------------------------------------------------------------//

Blender::Blender()
    : m_inputsA("Inputs A", new ImageDropView([this](juce::Component *p_caller, const juce::StringArray &files)
                                              { return imagesUpdated(p_caller, files); }))
    , m_inputsB("Inputs B", new ImageDropView([this](juce::Component *p_caller, const juce::StringArray &files)
                                              { return imagesUpdated(p_caller, files); }))
    , m_template("Template", new ImageDropView([this](juce::Component *p_caller, const juce::StringArray &files)
                                               { return imagesUpdated(p_caller, files); }))
    , m_output("Output", new ImageFrame())
{
    addAndMakeVisible(m_inputsA);
    addAndMakeVisible(m_inputsB);
    addAndMakeVisible(m_template);
    addAndMakeVisible(m_output);
}

//-------------------------------------------------------------------------------------------------//

std::unique_ptr<juce::Component> Blender::imagesUpdated(juce::Component *p_caller, const juce::StringArray &files)
{
    std::unique_ptr<juce::Component> p_imageDisplayer{ nullptr };
    if (files.size() == 1)
    {
        std::unique_ptr<ImageData> imageData{ std::make_unique<ImageData>(files[0].toStdString()) };
        p_imageDisplayer = std::make_unique<ImageFrame>(std::move(imageData));
    }
    else
    {
        auto parent{ p_caller->getParentComponent() };
        if (parent == &m_inputsA || parent == &m_inputsB)
        {
            p_imageDisplayer = std::make_unique<ImageList<MappedFileListModel>>(files);
        }
        else
        {
            p_imageDisplayer = std::make_unique<ImageList<FileListModel>>(files);
        }
    }

    juce::StringArray inImagesA{ m_inputsA.getComponent<ImageDropView>()->getImages() };
    juce::StringArray inImagesB{ m_inputsB.getComponent<ImageDropView>()->getImages() };
    juce::StringArray templateImages{ m_template.getComponent<ImageDropView>()->getImages() };

    ImageFrame *p_output{ m_output.getComponent<ImageFrame>() };

    p_output->reset();

    for (const auto &inImageA : inImagesA)
    {
        for (const auto &inImageB : inImagesB)
        {
            for (const auto &templateImage : templateImages)
            {
                ImageData inA{ inImageA.toStdString() };
                ImageData inB{ inImageB.toStdString() };
                ImageData tmp{ templateImage.toStdString() };
                std::unique_ptr<ImageData> out{ ImageManipulation::blendABFromTemplate(inA, inB, tmp) };
                p_output->setImage(std::move(out));
            }
        }
    }

    return std::move(p_imageDisplayer);
}

//-------------------------------------------------------------------------------------------------//

void Blender::resized()
{
    auto bounds{ getLocalBounds() };
    int fourthWidth{ bounds.getWidth() / 4 };

    auto left{ bounds.removeFromLeft(fourthWidth) };
    auto middleLeft{ bounds.removeFromLeft(fourthWidth) };
    auto middleRight{ bounds.removeFromLeft(fourthWidth) };
    auto right{ bounds.removeFromLeft(fourthWidth) };

    const int padding{ 4 };
    left.reduce(padding, padding);
    middleLeft.reduce(padding, padding);
    middleRight.reduce(padding, padding);
    right.reduce(padding, padding);

    left.setHeight(std::min(left.getWidth(), left.getHeight()));
    middleLeft.setHeight(std::min(middleLeft.getWidth(), middleLeft.getHeight()));
    middleRight.setHeight(std::min(middleRight.getWidth(), middleRight.getHeight()));
    right.setHeight(std::min(right.getWidth(), right.getHeight()));

    int sideLength{ std::min(left.getWidth(), left.getHeight()) };

    int centeredHeight{ (bounds.getHeight() - sideLength) / 2 };
    m_inputsA.setBounds(left.getX(), centeredHeight, sideLength, sideLength);
    m_inputsB.setBounds(middleLeft.getX(), centeredHeight, sideLength, sideLength);
    m_template.setBounds(middleRight.getX(), centeredHeight, sideLength, sideLength);
    m_output.setBounds(right.getX(), centeredHeight, sideLength, sideLength);
}

//-------------------------------------------------------------------------------------------------//
