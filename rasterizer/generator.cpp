#include "generator.h"

std::vector<uint8_t> BitmapGenerator::GetBitmap(int width, int height)
{
    const uint32_t rowPitch = width * TexturePixelSize;
    const uint32_t cellPitch = rowPitch >> 3;        // The width of a cell in the checkboard texture.
    const uint32_t cellHeight = width >> 3;    // The height of a cell in the checkerboard texture.
    const uint32_t textureSize = rowPitch * height;

    std::vector<uint8_t> data(textureSize);
    
    for (int row = 0; row < height; row++) {
        for (int column = 0; column < width; column++) {
            data[row * height + column] = 0x0F;
        }
    }

    return data;
}
