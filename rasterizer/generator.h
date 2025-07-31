#ifndef BITMAP_GENERATOR_H
#define BITMAP_GENERATOR_H

#include <vector>

class BitmapGenerator
{
public:
	std::vector<uint8_t> GetBitmap(int width, int height);

	static constexpr size_t TexturePixelSize = 4;
};

#endif