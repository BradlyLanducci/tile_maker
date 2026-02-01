#pragma once

#include <juce_animation/juce_animation.h>
#include <functional>

//-------------------------------------------------------------------------------------------------//

using ValueChangedCallback = std::function<void(float)>;

//-------------------------------------------------------------------------------------------------//

constexpr int ANIMATION_DURATION_MS{ 1000 };

class BackgroundAnimation : public juce::Component
{
public:
    BackgroundAnimation(ValueChangedCallback valueChangedCb);

    void start();

private:
    ValueChangedCallback m_valueChangedCb{ nullptr };
    juce::VBlankAnimatorUpdater m_updater;
    juce::Animator m_animator;
};

//-------------------------------------------------------------------------------------------------//
