#include <utility>
#include <iostream>
#include <map>
#include <cstring>
#include "image.hpp"
#include <tbb/tbb.h>

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
    for (size_t index = 0; index < size_x_; ++index) {
        delete[] pixels_tmp[index];
    }
	delete[] pixels_tmp;
}

void Image::ParallelSmoothing(size_t core_radius) {
    tbb::task_scheduler_init init;
    auto** pixels_tmp = new Pixel*[size_x_];
    //Slowly
    for (size_t index = 0; index < size_x_; ++index) {
        pixels_tmp[index] = new Pixel[size_y_];
    }
    //Equal
    for (size_t index = 0; index < size_x_; ++index) {
        memcpy(pixels_tmp[index], pixels_[index], size_y_ * sizeof(Pixel));
        memset(pixels_[index], 0, size_y_ * sizeof(Pixel));
    }
    class Body {
        const Pixel* const * const pixels_tmp_;
        Pixel** const pixels_;
        size_t core_radius_, size_y_;
    public:
        Body() = delete;
        Body(Pixel** pixels_tmp, Pixel** pixels,
             size_t core_radius, size_t size_y)
             : pixels_tmp_(pixels_tmp), pixels_(pixels), core_radius_(core_radius),
               size_y_(size_y) {
        }
        Body(const Body& rhs) = default;
        Body(Body&& rhs) noexcept = default;
        ~Body() = default;

        Body& operator=(const Body& rhs) = delete;
        Body& operator=(Body&& rhs) noexcept = delete;
        void operator()(const tbb::blocked_range<size_t>& range) const {
            size_t begin = range.begin(), end = range.end();
            uint64_t median_red, median_green, median_blue, divider;
            for (size_t index_x = begin; index_x < end; ++index_x) {
                for (size_t index_y = core_radius_; index_y != size_y_ - core_radius_; ++index_y) {
                    median_red = 0, median_green = 0, median_blue = 0;
                    for (size_t core_index_y = index_y - core_radius_;
                         core_index_y <= index_y + core_radius_; ++core_index_y) {
                        for (size_t core_index_x = index_x - core_radius_;
                             core_index_x <= index_x + core_radius_; ++core_index_x) {
                            median_red += pixels_tmp_[core_index_x][core_index_y].red;
                            median_green += pixels_tmp_[core_index_x][core_index_y].green;
                            median_blue += pixels_tmp_[core_index_x][core_index_y].blue;
                        }
                    }
                    divider = (core_radius_ * 2 + 1) * (core_radius_ * 2 + 1);
                    median_red /= divider;
                    median_green /= divider;
                    median_blue /= divider;
                    pixels_[index_x][index_y] = Pixel{static_cast<ColorType>(median_red),
                                                      static_cast<ColorType>(median_green),
                                                      static_cast<ColorType>(median_blue)};
                }
            }
        }
    } body(pixels_tmp, pixels_, core_radius, size_y_);
    tbb::parallel_for(tbb::blocked_range<size_t>(core_radius, size_x_ - core_radius), body);
    for (size_t index = 0; index < size_x_; ++index) {
        delete[] pixels_tmp[index];
    }
    delete[] pixels_tmp;
    init.terminate();
}
