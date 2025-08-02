#include "generator.h"
#include <chrono>
#include <numbers>

std::vector<uint8_t> BitmapGenerator::GetDefaultBitmap(int width, int height)
{
    const uint32_t textureSize = width * height * TexturePixelSize;

    std::vector<uint8_t> data(textureSize);
    
    for(auto &pixel : data)
    {
        pixel = 0x0F;
	}

    return data;
}

std::vector<uint8_t> BitmapGenerator::GetBitmap(int width, int height, size_t ms)
{
    const uint32_t textureSize = width * height * TexturePixelSize;

    std::vector<uint8_t> data(textureSize);
    auto colors = GenerateImage(width, height, ms);

    for (size_t i = 0; i < textureSize; i += TexturePixelSize) {
        data[i] = colors[i / 4].r;
        data[i+1] = colors[i / 4].g;
        data[i+2] = colors[i / 4].b;
        data[i+3] = colors[i / 4].a;
    }

    return data;
}

std::vector<RGBA8Color> BitmapGenerator::GenerateImage(int width, int height, size_t ms)
{
    std::vector<RGBA8Color> colors(width * height);

    float period = 1000.0;
    double norm = 0.5 * (1.0 + std::sin(2.0 * std::numbers::pi * double(ms) / period));
    uint8_t pulse = static_cast<uint8_t>(norm * 0xFF + 0.5);

    for (auto& color : colors) {
        color.r = 0x00;
        color.g = pulse;
        color.b = 0x00;
        color.a = 0xFF;
    }

    return colors;
}

