#include <ui/components/nine_slice.h>

//-------------------------------------------------------------------------------------------------//

NineSlice::NineSlice(const char *data, int bytes)
    : m_image(juce::ImageCache::getFromMemory(data, bytes))
{
}

//-------------------------------------------------------------------------------------------------//

/// Thanks pizza man
/// https://forum.juce.com/t/scale-9-images/26275/7
void NineSlice::draw(juce::Graphics &g, const juce::Rectangle<int> &localBounds)
{
    const int dw{ localBounds.getWidth() };
    const int dh{ localBounds.getHeight() };
    const int iw{ m_image.getWidth() };
    const int ih{ m_image.getHeight() };

    const int sliceLeft{ m_image.getWidth() / 3 };
    const int sliceTop{ m_image.getHeight() / 3 };
    const int sliceRight{ 2 * m_image.getWidth() / 3 };
    const int sliceBottom{ 2 * m_image.getHeight() / 3 };

    const int sCenterWidth{ iw - sliceLeft - (iw - sliceRight) };
    const int sCenterHeight{ ih - sliceTop - (ih - sliceBottom) };
    const int dRightX{ dw - (iw - sliceRight) };
    const int dBottomY{ dh - (ih - sliceBottom) };
    const int dCenterHeight{ dh - sliceTop - (ih - sliceBottom) };
    const int dCenterWidth{ dw - sliceLeft - (iw - sliceRight) };
    const int bottomHeight{ ih - sliceBottom };
    const int rightWidth{ iw - sliceRight };

    // left column
    g.drawImage(m_image, 0, 0, sliceLeft, sliceTop, 0, 0, sliceLeft, sliceTop);
    g.drawImage(m_image, 0, sliceTop, sliceLeft, dCenterHeight, 0, sliceTop, sliceLeft, sCenterHeight);
    g.drawImage(m_image, 0, dBottomY, sliceLeft, bottomHeight, 0, sliceBottom, sliceLeft, bottomHeight);
    // center column
    g.drawImage(m_image, sliceLeft, 0, dCenterWidth, sliceTop, sliceLeft, 0, sCenterWidth, sliceTop);
    g.drawImage(m_image, sliceLeft, sliceTop, dCenterWidth, dCenterHeight, sliceLeft, sliceTop, sCenterWidth,
                sCenterHeight);
    g.drawImage(m_image, sliceLeft, dBottomY, dCenterWidth, bottomHeight, sliceLeft, sliceBottom, sCenterWidth,
                bottomHeight);
    // right column
    g.drawImage(m_image, dRightX, 0, rightWidth, sliceTop, sliceRight, 0, rightWidth, sliceTop);
    g.drawImage(m_image, dRightX, sliceTop, rightWidth, dCenterHeight, sliceRight, sliceTop, rightWidth, sCenterHeight);
    g.drawImage(m_image, dRightX, dBottomY, rightWidth, bottomHeight, sliceRight, sliceBottom, rightWidth,
                bottomHeight);
}

//-------------------------------------------------------------------------------------------------//
