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

    float period = 1000.0;
    double norm = 0.5 * (1.0 + std::sin(2.0 * std::numbers::pi * double(ms) / period));
    uint8_t color = static_cast<uint8_t>(norm * 0xFF + 0.5);

    for (size_t i = 0; i < textureSize; i += TexturePixelSize) {
        data[i + 1] = color;
        data[i + TexturePixelSize - 1] = 0xFF;
    }

    return data;
}

