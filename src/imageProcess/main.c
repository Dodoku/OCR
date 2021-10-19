#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_pixels.h>

#include "../tools/image.h"
#include "rotate.h"
#include "contrast.h"
#include "greyScale.h"

int main() {
    SDL_Surface* image = load("../../tests/assets/image_01.jpeg");
    SDL_Surface* grey = to_black_and_white(image);
    save(grey, "../../tests/assets/grey.jpeg");
    return 0;
}
