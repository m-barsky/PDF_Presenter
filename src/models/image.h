#pragma once

#include <vector>
#include <cstdint>

class image {
    using uint8_t = std::uint8_t;
public:
    image();
    image(const std::vector<uint8_t>& data, int width, int height);
    image(uint8_t r, uint8_t g, uint8_t b, int width, int height);
    ~image() = default;

    constexpr int width() const {
        return m_width;
    }
    
    constexpr int height() const {
        return m_height;
    }

    const std::vector<uint8_t>& data() const {
        return m_data;
    }

private:
    std::vector<uint8_t> m_data;
    int m_width;
    int m_height;

    static constexpr int CHANNELS_PER_PIXEL = 3;
};

