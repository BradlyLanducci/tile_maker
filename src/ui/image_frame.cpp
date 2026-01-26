#include <ui/image_frame.h>

#include <image/image_data.h>

//-------------------------------------------------------------------------------------------------//

ImageFrame::ImageFrame(std::unique_ptr<ImageData> imageData)
{
    setImage(std::move(imageData));
}

//-------------------------------------------------------------------------------------------------//

void ImageFrame::paint(juce::Graphics &g)
{
    g.drawImage(m_image, getLocalBounds().toFloat());
}

//-------------------------------------------------------------------------------------------------//

void ImageFrame::setImage(std::unique_ptr<ImageData> p_imageData)
{
    int w{ p_imageData->width };
    int h{ p_imageData->height };
    const uint8_t *src{ p_imageData->p_data };

    m_image = juce::Image(juce::Image::ARGB, w, h, true);

    juce::Image::BitmapData dest(m_image, juce::Image::BitmapData::writeOnly);

    for (int y = 0; y < h; ++y)
    {
        uint8_t *d{ dest.getLinePointer(y) };
        for (int x = 0; x < w; ++x)
        {
            const uint8_t *s = src + (y * w + x) * p_imageData->channels;

            // JUCE expects this in a ARGB format so we reorder it here. It's convenient to leave it internally as RBGA
            // for image writing
            uint8_t r = s[0];
            uint8_t g = s[1];
            uint8_t b = s[2];
            uint8_t a = s[3];

            d[0] = b;
            d[1] = g;
            d[2] = r;
            d[3] = a;

            s += p_imageData->channels;
            d += p_imageData->channels;
        }
    }

    repaint();
}

//-------------------------------------------------------------------------------------------------//

void ImageFrame::reset()
{
    m_image.clear(getBounds());
}

//-------------------------------------------------------------------------------------------------//
