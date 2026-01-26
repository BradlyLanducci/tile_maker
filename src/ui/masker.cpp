#include <ui/masker.h>

//-------------------------------------------------------------------------------------------------//

Masker::Masker()
    : m_input("Input")
    , m_mask("Mask")
{
    addAndMakeVisible(m_input);
    addAndMakeVisible(m_mask);
}

//-------------------------------------------------------------------------------------------------//

void Masker::resized()
{
    auto bounds{ getLocalBounds() };
    int halfWidth{ bounds.getWidth() / 2 };

    auto leftSide{ bounds.removeFromRight(halfWidth) };
    auto rightSide{ bounds.removeFromLeft(halfWidth) };

    const int padding{ 4 };
    leftSide.reduce(padding, padding);
    rightSide.reduce(padding, padding);

    leftSide.setHeight(std::min(leftSide.getWidth(), leftSide.getHeight()));
    rightSide.setHeight(std::min(leftSide.getWidth(), leftSide.getHeight()));

    int sideLength{ std::min(leftSide.getWidth(), leftSide.getHeight()) };

    int centeredHeight{ (bounds.getHeight() - sideLength) / 2 };
    m_input.setBounds(leftSide.getX(), centeredHeight, sideLength, sideLength);
    m_mask.setBounds(rightSide.getX(), centeredHeight, sideLength, sideLength);
}

//-------------------------------------------------------------------------------------------------//
