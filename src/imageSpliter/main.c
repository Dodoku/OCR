#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_pixels.h>

#include "hough.h"
#include "../tools/image.h"

int main() {
    SDL_Surface* image = load("tests/assets/grey.jpeg");
    hough_transform(image);
    return 0;
}
