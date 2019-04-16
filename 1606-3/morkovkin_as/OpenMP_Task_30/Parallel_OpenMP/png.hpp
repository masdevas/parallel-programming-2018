#ifndef MPI_TASK2_27_PNG_H
#define MPI_TASK2_27_PNG_H

#include <string>
#include <random>

#include "image.hpp"

class PngProcessor {
public:
    PngProcessor() = default;

    PngProcessor(const PngProcessor& reader) = default;

    PngProcessor(PngProcessor&& reader) noexcept = default;

    ~PngProcessor() = default;

    PngProcessor& operator=(const PngProcessor& reader) = delete;

    PngProcessor& operator=(PngProcessor&& reader) noexcept = default;

    Image Read(const std::string& image_name);

    void Write(const Image& image);

    Image Generate(uint32_t size_x, uint32_t size_y);
};

#endif
