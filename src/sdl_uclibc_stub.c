#include <math.h>

int SDL_uclibc_isinf(double x) {
    return isinf(x);
}

// SDL required this in order to compile on Windows