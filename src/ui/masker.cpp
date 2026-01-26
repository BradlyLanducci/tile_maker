#include <ui/masker.h>
#include "masker.h"
//-------------------------------------------------------------------------------------------------//

Masker::Masker()
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

    const int padding{ 5 };
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
