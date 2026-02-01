#include <ui/main_content.h>
#include <ui/editors/masker.h>
#include <ui/editors/blender.h>
#include <ui/editors/noiser.h>
#include <ui/theme/theme.h>
#include <BinaryData.h>

#include <magic_enum/magic_enum.hpp>

//-------------------------------------------------------------------------------------------------//

MainContent::MainContent()
    : m_animator(
          [this](float value)
          {
              const float easeInEnd{ 0.3f };
              const float easeOutStart{ 0.7f };
              bool animating{ value < easeInEnd || value > easeOutStart };
              if (animating)
              {
                  bool animatingIn{ value < easeInEnd };
                  if (animatingIn)
                  {
                      value = juce::jmap(value, 0.f, easeInEnd, 0.f, 0.5f);
                      m_backgroundX = (float)getWidth() * -value;
                      m_backgroundY = (float)getHeight() * value;
                  }
                  else
                  {
                      value = 1.f - juce::jmap(value, easeOutStart, 1.f, 0.5f, 1.f);
                      m_backgroundX = (float)getWidth() * -value;
                      m_backgroundY = (float)getHeight() * value;
                  }
                  repaint();
              }
          })
    , m_backgroundImage(
          juce::ImageCache::getFromMemory(BinaryData::background_gradient_png, BinaryData::background_gradient_pngSize))
    , m_topBar([this](Theme::EditorType type) { setEditor(type); })
    , m_generate("Generate")
{
    setEditor(Theme::EditorType::Masker);

    addAndMakeVisible(m_animator);

    addAndMakeVisible(m_topBar);
    addAndMakeVisible(*mp_editor);
    addAndMakeVisible(m_directoryChooser);
    addAndMakeVisible(m_generate);

    m_directoryChooser.setLookAndFeel(&m_look);
    m_generate.setLookAndFeel(&m_look);

    m_generate.onClick = [this]()
    {
        if (mp_editor)
        {
            mp_editor->generate(m_directoryChooser.getOutputDirectory());
        }
    };
}

//-------------------------------------------------------------------------------------------------//

MainContent::~MainContent()
{
    m_directoryChooser.setLookAndFeel(nullptr);
    m_generate.setLookAndFeel(nullptr);
}

//-------------------------------------------------------------------------------------------------//

void MainContent::paint(juce::Graphics &g)
{
    auto bounds{ getLocalBounds().toFloat() };

    g.fillAll(juce::Colour(106, 99, 163));
    g.drawImage(m_backgroundImage, juce::Rectangle<float>(m_backgroundX, m_backgroundY, (float)bounds.getWidth(),
                                                          (float)bounds.getHeight()));

    g.setFont(Theme::HUMONGOUS_FONT_SIZE);
    g.setColour(Theme::LIGHT_TEXT);
    juce::String editorName{ juce::String{ magic_enum::enum_name<Theme::EditorType>(m_editorType).data() } };
    g.drawText(editorName, bounds.removeFromBottom(100).removeFromLeft(bounds.getWidth() / 3.f),
               juce::Justification::centred);
}

//-------------------------------------------------------------------------------------------------//

void MainContent::resized()
{
    auto bounds{ getLocalBounds() };

    auto top{ bounds.removeFromTop(75) };
    top.reduce(Theme::DEFAULT_PADDING, Theme::DEFAULT_PADDING);
    m_topBar.setBounds(top);

    auto bottom{ bounds.removeFromBottom(100).removeFromRight(2 * bounds.getWidth() / 3) };

    auto bottomLeft{ bottom.removeFromLeft(getWidth() / 2) };
    auto dirBounds{ bottomLeft.reduced(10).withWidth(200) };
    m_directoryChooser.setBounds(
        dirBounds.withX(dirBounds.getX() + (bottomLeft.getWidth() - dirBounds.getWidth()) / 2));

    auto genBounds{ bottom.removeFromBottom(75).reduced(10).withWidth(200) };
    m_generate.setBounds(genBounds.withX(genBounds.getX() + (bottom.getWidth() - genBounds.getWidth()) / 2));

    if (mp_editor)
    {
        const int editorPadding{ 50 };
        bounds.reduce(editorPadding, editorPadding);
        mp_editor->setBounds(bounds);
    }
}

//-------------------------------------------------------------------------------------------------//

void MainContent::setEditor(Theme::EditorType type)
{
    m_animator.start();
    m_editorType = type;
    switch (type)
    {
    case Theme::EditorType::Masker:
        mp_editor = std::make_unique<Masker>();
        break;
    case Theme::EditorType::Blender:
        mp_editor = std::make_unique<Blender>();
        break;
    case Theme::EditorType::Noiser:
        mp_editor = std::make_unique<Noiser>();
        break;
    case Theme::EditorType::None:
    default:
        return;
    }

    addAndMakeVisible(*mp_editor);
    repaint();
    resized();
}

//-------------------------------------------------------------------------------------------------//
