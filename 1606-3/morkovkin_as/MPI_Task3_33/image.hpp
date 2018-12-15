#ifndef MPI_TASK2_27_IMAGE_HPP
#define MPI_TASK2_27_IMAGE_HPP

#include <string>
#include <cmath>

#include "pixel.hpp"

class Image {
public:
    Image() = delete;

    Image(const Image& image);

    Image(Image&& image) noexcept;

    explicit Image(Pixel** pixels, uint32_t size_x, uint32_t size_y);

    ~Image();

    Image& operator=(const Image& image);

    Image& operator=(Image&& image) noexcept;

    void NonParallelSobelFiltering();

    uint32_t SizeX() {
        return size_x_;
    }

    uint32_t SizeY() {
        return size_y_;
    }

    Pixel* Data() {
        return pixels_;
    }

    void SetData(Pixel* pixels) {
        pixels_ = pixels;
    }

private:
    Pixel* pixels_;

    uint32_t size_x_;

    uint32_t size_y_;

    Pixel ApplyOperator(uint32_t x, uint32_t y, int kernel[3][3]);
};


#endif
