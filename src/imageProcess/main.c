#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_pixels.h>
#include <err.h>
#include <string.h>

#include "../tools/image.h"
#include "rotate.h"
#include "contrast.h"
#include "grayscale.h"
#include "noise_reduction.h"

int main(int argc, char *argv[])
 {
    SDL_Surface* image = load("tests/assets/image_02.jpeg");


    //image = gaussian_blur(image, 5);
    image = to_grayscale(image);
    image = to_grayscale(image);
    image = adaptative_treashold(image);
    save(image, "generated1.jpeg");
    printf("blur -> picture saved\n");

    return 0;
}
