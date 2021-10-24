#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_pixels.h>
#include <err.h>
#include <string.h>

#include "../tools/image.h"
#include "rotate.h"
#include "contrast.h"
#include "greyScale.h"
#include "noise_reduction.h"

int main(int argc, char *argv[]) {
    if(argc == 1){
        printf("Use greyscale + path-src + path-dest\n(to put a picture in grayscale)\n\n");
        printf("Use rotate + path-src + path-dest + degree\n(to rotate a picture with a degree in degree)\n\n");
        printf("Use blur + path-rc + path-dest + n\n(to apply the gaussian_blur n times)\n");
        return 1;
    }

    if(!strcmp(argv[1],"greyscale")){
        if(argc != 4)
            errx(1,"greyscale -> wrong number of argument\n");
        SDL_Surface* image = load(argv[2]);
        image = to_greyscale(image);
        save(image, argv[3]);
        printf("greyscale -> picture saved\n");
        return 0;
    }

    if(!strcmp(argv[1],"rotate")){
        if(argc != 5)
            errx(1,"rotate -> wrong number of argument\n");
        SDL_Surface* image = load(argv[2]);
        image = rotate(image, -atoi(argv[4])*3.14/180);
        save(image, argv[3]);
        printf("rotate -> picture saved\n");
        return 0;
    }

    if(!strcmp(argv[1],"blur")){
        if(argc != 5)
            errx(1,"blur -> wrong number of argument\n");
        SDL_Surface* image = load(argv[2]);
        image = gaussian_blur(image, atoi(argv[4]));
        save(image, argv[3]);
        printf("blur -> picture saved\n");
        return 0;
    }


    printf("wrong argument\n");
    return 0;
}
