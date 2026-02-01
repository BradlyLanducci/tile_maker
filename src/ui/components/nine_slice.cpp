#include <ui/components/nine_slice.h>

//-------------------------------------------------------------------------------------------------//

NineSlice::NineSlice(const char *data, int bytes)
    : m_image(juce::ImageCache::getFromMemory(data, bytes))
{
}

//-------------------------------------------------------------------------------------------------//

void NineSlice::draw(juce::Graphics &g, const juce::Rectangle<int> &localBounds)
{
    const int iw{ m_image.getWidth() };
    const int ih{ m_image.getHeight() };

    const int left{ 8 };
    const int right{ 8 };
    const int top{ 8 };
    const int bottom{ 8 };

    const int minW{ left + right };
    const int minH{ top + bottom };

    const int dw{ localBounds.getWidth() };
    const int dh{ localBounds.getHeight() };
    jassert(dw > minW && dh > minH);

    const int srcCenterW{ iw - left - right };
    const int srcCenterH{ ih - top - bottom };

    const int dstCenterW{ dw - left - right };
    const int dstCenterH{ dh - top - bottom };

    const int x0{ localBounds.getX() };
    const int y0{ localBounds.getY() };
    const int x1{ x0 + left };
    const int x2{ x0 + left + dstCenterW };
    const int y1{ y0 + top };
    const int y2{ y0 + top + dstCenterH };

    g.drawImage(m_image, x0, y0, left, top, 0, 0, left, top);
    g.drawImage(m_image, x1, y0, dstCenterW, top, left, 0, srcCenterW, top);
    g.drawImage(m_image, x2, y0, right, top, iw - right, 0, right, top);

    g.drawImage(m_image, x0, y1, left, dstCenterH, 0, top, left, srcCenterH);
    g.drawImage(m_image, x1, y1, dstCenterW, dstCenterH, left, top, srcCenterW, srcCenterH);
    g.drawImage(m_image, x2, y1, right, dstCenterH, iw - right, top, right, srcCenterH);

    g.drawImage(m_image, x0, y2, left, bottom, 0, ih - bottom, left, bottom);
    g.drawImage(m_image, x1, y2, dstCenterW, bottom, left, ih - bottom, srcCenterW, bottom);
    g.drawImage(m_image, x2, y2, right, bottom, iw - right, ih - bottom, right, bottom);
}

//-------------------------------------------------------------------------------------------------//
