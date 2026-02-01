#pragma once

#include <ui/theme/theme.h>

#include <juce_animation/juce_animation.h>
#include <functional>

//-------------------------------------------------------------------------------------------------//

constexpr int ANIMATION_DURATION_MS{ 1000 };

class BackgroundAnimation : public juce::Component
{
public:
    BackgroundAnimation(juce::Component *p_parent);

    void animate(Theme::EditorType type);
    void draw(juce::Graphics &g, juce::Rectangle<float> bounds);

private:
    juce::VBlankAnimatorUpdater m_updater;
    juce::Animator m_animator;

    float m_backgroundX{};
    float m_backgroundY{};

    juce::Image m_backgroundImage;
    juce::Image m_maskerImage;
    juce::Image m_blenderImage;
    juce::Image m_noiserImage;
    juce::Image m_editorImage;

    Theme::EditorType m_editorToTransitionTo{ Theme::EditorType::None };
};

//-------------------------------------------------------------------------------------------------//
