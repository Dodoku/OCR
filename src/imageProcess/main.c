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
    SDL_Surface* image1 = load("tests/assets/image_01.jpeg");
    SDL_Surface* image2 = load("tests/assets/image_02.jpeg");
    SDL_Surface* image3 = load("tests/assets/image_03.jpeg");
    SDL_Surface* image4 = load("tests/assets/image_04.jpeg");
    SDL_Surface* image5 = load("tests/assets/image_05.jpeg");
    SDL_Surface* image6 = load("tests/assets/image_06.jpeg");

    image1 = gaussian_blur(image1, 5);
    image1 = otsu(image1,20);
    save(image1, "generated1.jpeg");
    printf("blur -> picture saved\n");

    image2 = gaussian_blur(image2, 5);
    image2 = otsu(image2,20);
    save(image2, "generated2.jpeg");
    printf("blur -> picture saved\n");

    image3 = gaussian_blur(image3, 5);
    image3 = otsu(image3,20);
    save(image3, "generated3.jpeg");
    printf("blur -> picture saved\n");

    image4 = gaussian_blur(image4, 5);
    image4 = otsu(image4,20);
    save(image4, "generated4.jpeg");
    printf("blur -> picture saved\n");

    image5 = gaussian_blur(image5, 5);
    image5 = otsu(image5,20);
    save(image5, "generated5.jpeg");
    printf("blur -> picture saved\n");

    image6 = gaussian_blur(image6, 5);
    image6 = otsu(image6,20);
    save(image6, "generated6.jpeg");
    printf("blur -> picture saved\n");
    return 0;
}
