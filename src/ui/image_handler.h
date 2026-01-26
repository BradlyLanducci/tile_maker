#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

//-------------------------------------------------------------------------------------------------//

class ImageHandler
    : public juce::Component
    , public juce::FileDragAndDropTarget
{
public:
    bool isInterestedInFileDrag(const juce::StringArray &files) override;
    void filesDropped(const juce::StringArray &files, int x, int y) override;

    void paint(juce::Graphics &g) override;

    void fileDragEnter(const juce::StringArray &files, int x, int y) override;
    void fileDragExit(const juce::StringArray &files) override;

    //-------------------------------------------------------------------------------------------------//

private:
    bool isValidType(juce::String file);

    bool m_hovered{ false };

    std::array<std::string, 3> m_validTypes{ ".png", ".jpeg", ".jpg" };

    std::unique_ptr<juce::Component> mp_imageDisplayer{ nullptr };
};

//-------------------------------------------------------------------------------------------------//
