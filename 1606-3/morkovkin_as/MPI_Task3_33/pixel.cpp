#include "pixel.hpp"

ColorType Clamp(int value, ColorType min, ColorType max) {
    if (value > max) {
        return max;
    } else if (value < min) {
        return min;
    } else {
        return static_cast<ColorType>(value);
    }
}