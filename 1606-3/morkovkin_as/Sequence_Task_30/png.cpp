#include "png.hpp"
#include <iostream>

Image PngProcessor::Read(const std::string& image_name) {
    throw "Read() not implemented";
}

void PngProcessor::Write(const Image& image) {
    throw "Write() not implemented";
}

Image PngProcessor::Generate(uint32_t size_x, uint32_t size_y) {
	auto** pixels = new Pixel*[size_x];//[size_y];
	for (size_t index = 0; index < size_x; ++index) {
		pixels[index] = new Pixel[size_y];
	}
    std::random_device dev;
    std::mt19937 gen(dev());
    std::uniform_int_distribution<unsigned> dist(0, 255);
	for (size_t x_coord = 0; x_coord < size_x; ++x_coord) {
		for (size_t y_coord = 0; y_coord < size_y; ++y_coord) {
			pixels[x_coord][y_coord] = Pixel{static_cast<ColorType>(dist(gen)),
									         static_cast<ColorType>(dist(gen)),
											 static_cast<ColorType>(dist(gen)) };
		}
    }
    Image res(&pixels, size_x, size_y);
    return (res);
}