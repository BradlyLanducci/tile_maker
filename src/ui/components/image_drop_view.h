#pragma once

//-------------------------------------------------------------------------------------------------//

#include <ui/components/image_list.h>

#include <juce_gui_basics/juce_gui_basics.h>

//-------------------------------------------------------------------------------------------------//

using FactoryCallback = std::function<std::unique_ptr<juce::Component>(juce::Component *, juce::ValueTree)>;

class ImageDropView final
    : public juce::Component
    , public juce::FileDragAndDropTarget
{
public:
    explicit ImageDropView(juce::ValueTree tree, FactoryCallback factoryCb);

    juce::ValueTree getImages();

    bool isInterestedInFileDrag(const juce::StringArray &files) override;
    void filesDropped(const juce::StringArray &files, int x, int y) override;

    void paint(juce::Graphics &g) override;

    void fileDragEnter(const juce::StringArray &files, int x, int y) override;
    void fileDragExit(const juce::StringArray &files) override;

private:
    bool isValidType(juce::String file);

    juce::StringArray m_images;

    FactoryCallback m_factoryCb;

    bool m_hovered{ false };

    std::array<std::string, 3> m_validTypes{ ".png", ".jpeg", ".jpg" };

    std::unique_ptr<juce::Component> mp_imageDisplayer{ nullptr };

    juce::ValueTree m_tree;
};

//-------------------------------------------------------------------------------------------------//
