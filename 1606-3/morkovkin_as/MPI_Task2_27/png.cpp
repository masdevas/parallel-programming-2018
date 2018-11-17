#include "png.hpp"
#include <iostream>

Image PngProcessor::Read(const std::string& image_name) {
    throw "Read() not implemented";
}

void PngProcessor::Write(const Image& image) {
    throw "Write() not implemented";
}

Image PngProcessor::Generate(uint32_t size_x, uint32_t size_y) {
    auto* pixels = new Pixel[size_x * size_y];
    std::random_device dev;
    std::mt19937 gen(dev());
    std::uniform_int_distribution<ColorType> dist(0, 255);
    for (uint32_t i = 0; i < size_x * size_y; ++i) {
        pixels[i] = Pixel{dist(gen), dist(gen), dist(gen)};
    }
    Image res(&pixels, size_x, size_y);
    return (res);
}