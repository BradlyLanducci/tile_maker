#include <ui/components/image_frame.h>
#include <processing/image_data.h>
#include <ui/utilities/theme.h>

//-------------------------------------------------------------------------------------------------//

ImageFrame::ImageFrame(const juce::String &placeholderText)
    : m_placeholderText(placeholderText)
{
}

//-------------------------------------------------------------------------------------------------//

void ImageFrame::paint(juce::Graphics &g)
{
    auto bounds{ getLocalBounds() };

    if (m_hasImage)
    {
        g.drawImage(m_image, bounds.toFloat(),
                    juce::RectanglePlacement::centred | juce::RectanglePlacement::onlyReduceInSize);
    }
    else
    {
        g.setFont(Theme::NORMAL_FONT_SIZE);
        g.setColour(juce::Colours::white);
        g.drawText(m_placeholderText, bounds, juce::Justification::centred);
    }
}

//-------------------------------------------------------------------------------------------------//

void ImageFrame::setImage(std::unique_ptr<ImageData> p_imageData)
{
    m_hasImage = true;
    int numChannels{ p_imageData->channels };

    if (numChannels < 3 || numChannels > 4)
    {
        return;
    }

    if (numChannels == 4)
    {
        RGBAToARGB(p_imageData.get());
    }
    else if (numChannels == 3)
    {
        RGBToRGB(p_imageData.get());
    }

    repaint();
}

//-------------------------------------------------------------------------------------------------//

void ImageFrame::reset()
{
    m_hasImage = false;
    m_image.clear(getBounds());
    repaint();
}

//-------------------------------------------------------------------------------------------------//

void ImageFrame::RGBAToARGB(ImageData *p_imageData)
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
}

//-------------------------------------------------------------------------------------------------//

void ImageFrame::RGBToRGB(ImageData *p_imageData)
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

            uint8_t r = s[0];
            uint8_t g = s[1];
            uint8_t b = s[2];

            d[0] = b;
            d[1] = g;
            d[2] = r;

            s += p_imageData->channels;
            d += p_imageData->channels;
        }
    }
}

//-------------------------------------------------------------------------------------------------//
