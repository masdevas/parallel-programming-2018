#include <utility>
#include <iostream>
#include <map>
#include <cstring>
#include "image.hpp"

Image::Image(const Image& image) : size_x_(image.size_x_), size_y_(image.size_y_) {
    pixels_ = new Pixel[size_x_ * size_y_];
    memcpy(pixels_, image.pixels_, size_x_ * size_y_ * sizeof(Pixel));
}

Image::Image(Image&& image) noexcept : pixels_(image.pixels_), size_x_(image.size_x_),
                                       size_y_(image.size_y_) {
    image.pixels_ = nullptr;
    image.size_x_ = 0;
    image.size_y_ = 0;
}

Image::Image(Pixel** pixels, uint32_t size_x, uint32_t size_y) : pixels_(*pixels),
                                                                 size_x_(size_x),
                                                                 size_y_(size_y) {
    *pixels = nullptr;
}

Image::~Image() {
    delete[] pixels_;
}

Image& Image::operator=(Image&& image) noexcept {
    delete[] pixels_;
    pixels_ = image.pixels_;
    size_x_ = image.size_x_;
    size_y_ = image.size_y_;
    image.pixels_ = nullptr;
    image.size_x_ = 0;
    image.size_y_ = 0;
    return *this;
}

Image& Image::operator=(const Image& image) {
    size_x_ = image.size_x_;
    size_y_ = image.size_y_;
    pixels_ = new Pixel[size_x_ * size_y_];
    memcpy(pixels_, image.pixels_, size_x_ * size_y_ * sizeof(Pixel));
    return *this;
}
