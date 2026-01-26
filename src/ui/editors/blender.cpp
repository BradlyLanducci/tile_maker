#include <ui/editors/blender.h>
#include <processing/image_manipulation.h>
#include <ui/components/image_frame.h>
#include <ui/models/mapped_file_list_model.h>
#include <ui/models/file_list_model.h>
#include <ui/components/image_list.h>

//-------------------------------------------------------------------------------------------------//

Blender::Blender()
    : m_inputs("Inputs", new ImageDropView([this](juce::Component *p_caller, const juce::StringArray &files)
                                           { return imagesUpdated(p_caller, files); }))
    , m_template("Template", new ImageDropView([this](juce::Component *p_caller, const juce::StringArray &files)
                                               { return imagesUpdated(p_caller, files); }))
    , m_output("Output", new ImageFrame())
{
    addAndMakeVisible(m_inputs);
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
        if (parent == &m_inputs)
        {
            p_imageDisplayer = std::make_unique<ImageList<MappedFileListModel>>(files);
        }
        else
        {
            p_imageDisplayer = std::make_unique<ImageList<FileListModel>>(files);
        }
    }

    juce::StringArray inImages{ m_inputs.getComponent<ImageDropView>()->getImages() };
    juce::StringArray maskImages{ m_template.getComponent<ImageDropView>()->getImages() };

    ImageFrame *p_output{ m_output.getComponent<ImageFrame>() };

    p_output->reset();

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

    return std::move(p_imageDisplayer);
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
    m_inputs.setBounds(left.getX(), centeredHeight, sideLength, sideLength);
    m_template.setBounds(middle.getX(), centeredHeight, sideLength, sideLength);
    m_output.setBounds(right.getX(), centeredHeight, sideLength, sideLength);
}

//-------------------------------------------------------------------------------------------------//
