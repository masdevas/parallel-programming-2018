#ifndef MPI_TASK2_27_PIXEL_HPP
#define MPI_TASK2_27_PIXEL_HPP

using ColorType = unsigned char;

ColorType Clamp(int value, ColorType min, ColorType max);

struct Pixel {
    ColorType red;

    ColorType green;

    ColorType blue;


    Pixel operator+(const Pixel& pixel) const {
        return Pixel{Clamp(red + pixel.red, 0, 255),
                     Clamp(green + pixel.green, 0, 255),
                     Clamp(blue + pixel.blue, 0, 255)};
    }

    bool operator==(const Pixel& pixel) const {
        return red == pixel.red && green == pixel.green && blue == pixel.blue;
    }

    bool operator!=(const Pixel& pixel) const {
        return !(*this == pixel);
    }
};

#endif
