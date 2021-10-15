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
    char s1[] = "0.jpeg";
    for(int i = 1; i < 7; i++){
        s[22] = '0'+i;
        s1[0] = '0'+i;
        SDL_Surface* image = load(s);
        save(image, s1);
    }

    return 0;
}
