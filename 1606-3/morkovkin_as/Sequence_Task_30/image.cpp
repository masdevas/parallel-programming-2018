#include <utility>
#include <iostream>
#include <map>
#include <cstring>
#include "image.hpp"

Image::Image(const Image& image) : size_x_(image.size_x_), size_y_(image.size_y_) {
    pixels_ = new Pixel*[size_x_];
	for (size_t index = 0; index < size_x_; ++index) {
		pixels_[index] = new Pixel[size_y_];
		memcpy(pixels_[index], image.pixels_[index], size_y_ * sizeof(Pixel));
	}
}

Image::Image(Image&& image) noexcept : pixels_(image.pixels_), size_x_(image.size_x_),
                                       size_y_(image.size_y_) {
    image.pixels_ = nullptr;
    image.size_x_ = 0;
    image.size_y_ = 0;
}

Image::Image(Pixel*** pixels, uint32_t size_x, uint32_t size_y) : pixels_(*pixels),
                                                                 size_x_(size_x),
                                                                 size_y_(size_y) {
    *pixels = nullptr;
}

Image::~Image() {
	for (size_t index = 0; index < size_x_; ++index) {
		delete[] pixels_[index];
	}
    delete[] pixels_;
}

Image& Image::operator=(Image&& image) noexcept {
	for (size_t index = 0; index < size_x_; ++index) {
		delete[] pixels_[index];
	}
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
	for (size_t index = 0; index < size_x_; ++index) {
		delete[] pixels_[index];
	}
	delete[] pixels_;
	size_x_ = image.size_x_;
	size_y_ = image.size_y_;
	pixels_ = new Pixel*[size_x_];
	for (size_t index = 0; index < size_x_; ++index) {
		pixels_[index] = new Pixel[size_y_];
		memcpy(pixels_[index], image.pixels_[index], size_y_ * sizeof(Pixel));
	}
    return *this;
}

void Image::NonParallelSmoothing(size_t core_radius) {
	auto** pixels_tmp = new Pixel*[size_x_];
	for (size_t index = 0; index < size_x_; ++index) {
		pixels_tmp[index] = new Pixel[size_y_];
		memcpy(pixels_tmp[index], pixels_[index], size_y_ * sizeof(Pixel));
		memset(pixels_[index], 0, size_y_ * sizeof(Pixel));
	}
	for (size_t index_y = core_radius; index_y + core_radius < size_y_; ++index_y) {
		for (size_t index_x = core_radius; index_x + core_radius < size_x_; ++index_x) {
			uint64_t median_red = 0, median_green = 0, median_blue = 0;
			for (size_t core_index_y = index_y - core_radius; core_index_y <= index_y + core_radius; ++core_index_y) {
				for (size_t core_index_x = index_x - core_radius; core_index_x <= index_x + core_radius; ++core_index_x) {
					median_red += pixels_tmp[core_index_x][core_index_y].red;
					median_green += pixels_tmp[core_index_x][core_index_y].green;
					median_blue += pixels_tmp[core_index_x][core_index_y].blue;
				}
			}
			size_t divider = (core_radius * 2 + 1) * (core_radius * 2 + 1);
			median_red /= divider;
			median_green /= divider;
			median_blue /= divider;
			pixels_[index_x][index_y] = Pixel{static_cast<ColorType>(median_red),
											  static_cast<ColorType>(median_green),
											  static_cast<ColorType>(median_blue)};
		}
	}
	delete[] pixels_tmp;
}

/*void Image::NonParallelSmoothing(size_t core_radius) {
    auto* pixels_tmp = new Pixel[size_x_ * size_y_];
    memcpy(pixels_tmp, pixels_, size_x_ * size_y_ * sizeof(Pixel));
    memset(pixels_, 0, size_x_ * size_y_ * sizeof(Pixel));
    for (size_t index_y = core_radius; index_y + core_radius < size_y_; ++index_y) {
        for (size_t index_x = core_radius; index_x + core_radius < size_x_; ++index_x) {
            uint64_t median_red = 0, median_green = 0, median_blue = 0;
            int counter = 0;
            for (size_t core_index_y = index_y - core_radius; core_index_y <= index_y + core_radius; ++core_index_y) {
                for (size_t core_index_x = index_x - core_radius; core_index_x <= index_x + core_radius; ++core_index_x) {
                    median_red += pixels_tmp[core_index_x + core_index_y * size_x_].red;
                    median_green += pixels_tmp[core_index_x + core_index_y * size_x_].green;
                    median_blue += pixels_tmp[core_index_x + core_index_y * size_x_].blue;
                    counter++;
                }
            }
            size_t divider = (core_radius * 2 + 1) * (core_radius * 2 + 1);
            median_red /= divider;
            median_green /= divider;
            median_blue /= divider;
            pixels_[index_x + index_y * size_x_] = Pixel{static_cast<ColorType>(median_red),
                                                        static_cast<ColorType>(median_green),
                                                        static_cast<ColorType>(median_blue)};
        }
    }
    delete[] pixels_tmp;
}*/
