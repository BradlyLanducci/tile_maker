#include <ui/components/background_animation.h>
#include <BinaryData.h>

//-------------------------------------------------------------------------------------------------//

BackgroundAnimation::BackgroundAnimation(juce::Component *p_parent)
    : m_updater(this)
    , m_animator(juce::ValueAnimatorBuilder{}
                     .withDurationMs(ANIMATION_DURATION_MS)
                     .withValueChangedCallback(
                         [this, p_parent](auto value)
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
                                     m_backgroundX = (float)p_parent->getWidth() * -value;
                                     m_backgroundY = (float)p_parent->getHeight() * value;
                                 }
                                 else
                                 {
                                     value = 1.f - juce::jmap(value, easeOutStart, 1.f, 0.5f, 1.f);
                                     m_backgroundX = (float)p_parent->getWidth() * -value;
                                     m_backgroundY = (float)p_parent->getHeight() * value;
                                 }
                                 p_parent->repaint();
                             }
                             else if (m_editorToTransitionTo != Editor::Type::None)
                             {
                                 switch (m_editorToTransitionTo)
                                 {
                                 case Editor::Type::Masker:
                                     m_editorImage = m_maskerImage;
                                     break;
                                 case Editor::Type::Blender:
                                     m_editorImage = m_blenderImage;
                                     break;
                                 case Editor::Type::Noiser:
                                     m_editorImage = m_noiserImage;
                                     break;
                                 case Editor::Type::None:
                                 default:
                                     return;
                                 }

                                 m_editorToTransitionTo = Editor::Type::None;
                             }
                         })
                     .build())
    , m_backgroundImage(
          juce::ImageCache::getFromMemory(BinaryData::background_gradient_png, BinaryData::background_gradient_pngSize))
    , m_maskerImage(juce::ImageCache::getFromMemory(BinaryData::masker_png, BinaryData::masker_pngSize))
    , m_blenderImage(juce::ImageCache::getFromMemory(BinaryData::blender_png, BinaryData::blender_pngSize))
    , m_noiserImage(juce::ImageCache::getFromMemory(BinaryData::noiser_png, BinaryData::noiser_pngSize))
    , m_editorImage(m_maskerImage)
{
    m_updater.addAnimator(m_animator);
}

//-------------------------------------------------------------------------------------------------//

void BackgroundAnimation::animate(Editor::Type type)
{
    m_editorToTransitionTo = type;
    m_animator.start();
}

//-------------------------------------------------------------------------------------------------//

void BackgroundAnimation::draw(juce::Graphics &g, juce::Rectangle<float> bounds)
{
    g.fillAll(juce::Colour(106, 99, 163));
    g.drawImage(m_backgroundImage, juce::Rectangle<float>(m_backgroundX, m_backgroundY, (float)bounds.getWidth(),
                                                          (float)bounds.getHeight()));

    auto editorBounds{ bounds.removeFromBottom(m_editorImage.getHeight())
                           .removeFromLeft(m_editorImage.getWidth())
                           .withWidth(m_editorImage.getWidth())
                           .withHeight(m_editorImage.getHeight()) };
    g.drawImage(m_editorImage, editorBounds.withX(m_backgroundX + 100).withY(editorBounds.getY() + m_backgroundY - 50));
}

//-------------------------------------------------------------------------------------------------//
