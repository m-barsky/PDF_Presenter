#include "image.h"

#include <cassert>

using std::uint8_t;

image::image() : m_data(), m_width(0), m_height(0) {

}

image::image(const std::vector<uint8_t>& data, int width, int height) : m_data(data), m_width(width), m_height(height) {
    assert(data.size() == width * height * CHANNELS_PER_PIXEL);

}

image::image(uint8_t r, uint8_t g, uint8_t b, int width, int height) : m_data(width * height * CHANNELS_PER_PIXEL), m_width(width), m_height(height) {
    for (auto it = m_data.begin(); it < m_data.end(); ) {
        // image is stored as rgb24 internally
        *it++ = r;
        *it++ = g;
        *it = b;
    }
}

