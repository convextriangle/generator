#ifndef BITMAP_GENERATOR_H
#define BITMAP_GENERATOR_H

#include <vector>
#include "utils.h"

class BitmapGenerator
{
public:
	static std::vector<uint8_t> GetDefaultBitmap(int width, int height);
	std::vector<uint8_t> GetBitmap(int width, int height, size_t ms);

	static constexpr size_t TexturePixelSize = 4;
private:
	std::vector<RGBA8Color> GenerateImage(int width, int height, size_t ms);
};

#endif