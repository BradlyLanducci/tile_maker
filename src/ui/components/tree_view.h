#pragma once

#include <ui/components/directory_chooser.h>

#include <vdm_directory/vdm_directory.h>
#include <vdm_ui/vdm_ui.h>

//-------------------------------------------------------------------------------------------------//

class SelectionViewer
    : public juce::Component
    , public vdm::SelectionModelListener
{
public:
    ~SelectionViewer() override = default;

    void paint(juce::Graphics &g) override
    {
        auto b{ getLocalBounds() };

        b.reduce(2, 2);
        g.setColour(juce::Colours::black);
        g.drawLine(juce::Line{ b.getTopRight(), b.getBottomRight() }.toFloat(), 1.0f);
        g.drawText("selected trees:", b.removeFromTop(30), juce::Justification::centred);
        b.removeFromRight(7);

        for (const auto &tree : m_selectedTrees)
        {
            auto text = juce::File{ tree.getProperty(vdm::FilePathUpdateHandler::Key).toString() }.getFileName();

            b.removeFromTop(2);
            auto textBounds{ b.removeFromTop(20) };
            g.setColour(findColour(juce::TreeView::selectedItemBackgroundColourId));
            g.fillRoundedRectangle(textBounds.toFloat(), 5.0f);
            g.setColour(juce::Colours::black);
            g.drawText(text, textBounds.withTrimmedLeft(7), juce::Justification::left);
        }
    }

private:
    void onTreeSelectionChanged(juce::ValueTree tree) override
    {
        if (vdm::SelectionModel::IsSelected(tree))
            m_selectedTrees.insert(m_selectedTrees.begin(), tree);
        else
        {
            auto it = std::ranges::find_if(m_selectedTrees, [tree](auto t) { return t == tree; });
            if (it != m_selectedTrees.end())
                m_selectedTrees.erase(it);
        }

        repaint();
    }

    std::vector<juce::ValueTree> m_selectedTrees;
};

class TreeModel
{
public:
    TreeModel()
    {
        for (auto tree : model->getValueTree())
        {
            auto s{ tree.getType().toString() };
            DBG(s);
        }
        vdm::DirectoryModel::SetDirOpen(model->getValueTree(), true);
    }

    vdm::DirectoryModelSync sync;
    const std::unique_ptr<vdm::DirectoryModel> model{ vdm::DirectoryModelBuilder{
        juce::File{ juce::File::getSpecialLocation(juce::File::SpecialLocationType::userDocumentsDirectory) } }
                                                          .withFileNameUpdateHandler()
                                                          .withFileSizeUpdateHandler()
                                                          .withFileExtensionUpdateHandler()
                                                          .withFilePathUpdateHandler()
                                                          .withSync(sync)
                                                          .withFileFilter(
                                                              std::make_unique<vdm::RegexFilter>(".+\\.cpp"))
                                                          .build() };

    vdm::FileNameUpdateHandler nameUpdateHandler;
};

//-------------------------------------------------------------------------------------------------//

class TreeView : public vdm::TreeView
{
public:
    TreeView()
    {
        setValueTree(m_model.model->getValueTree());
        // addAndMakeVisible(m_chooser);
    }

    void resized() override
    {
        // m_chooser.setBounds(getLocalBounds());
    }

private:
    TreeModel m_model;

    // DirectoryChooser m_chooser;
};

//-------------------------------------------------------------------------------------------------//
