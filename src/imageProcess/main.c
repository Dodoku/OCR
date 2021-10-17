#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_pixels.h>

#include "../tools/image.h"
#include "rotate.h"
#include "contrast.h"
#include "greyScale.h"
#include "noise_reduction.h"

int main() {
    char s[] = "./tests/assets/image_00.jpeg";
    char s1[] = "tests/generated/0.jpeg";
    for(int i = 1; i < 7; i++){
        s[22] = '0'+i;
        s1[16] = '0'+i;
        SDL_Surface* image = load(s);
        //image = to_black_and_white(image);
        //image = noise_reduction(image,0.5);
        image = contrast(image,0.5);
        save(image, s1);
    }

    return 0;
}
