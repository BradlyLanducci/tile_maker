#include <ui/components/background_animation.h>

//-------------------------------------------------------------------------------------------------//

BackgroundAnimation::BackgroundAnimation(ValueChangedCallback valueChangedCb)
    : m_valueChangedCb(valueChangedCb)
    , m_updater(this)
    , m_animator(juce::ValueAnimatorBuilder{}
                     .withDurationMs(ANIMATION_DURATION_MS)
                     .withValueChangedCallback(
                         [this](auto value)
                         {
                             if (m_valueChangedCb)
                             {
                                 m_valueChangedCb(value);
                             }
                         })
                     .build())
{
    m_updater.addAnimator(m_animator);
}

//-------------------------------------------------------------------------------------------------//

void BackgroundAnimation::start()
{
    m_animator.start();
}

//-------------------------------------------------------------------------------------------------//
