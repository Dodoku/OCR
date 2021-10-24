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

int main(int argc, char *argv[]) {
    if(argc == 1){
        printf("\n\nUse all + '-' + '-'\n(to apply all the filters on all the pictures)\n\n");
        printf("Use all + path-src + path-dest\n(to apply all the filters)\n\n");
        printf("Use greyscale + path-src + path-dest\n(to put a picture in grayscale)\n\n");
        printf("Use rotate + path-src + path-dest + degree\n(to rotate a picture with a degree in degree)\n\n");
        printf("Use blur + path-rc + path-dest + n\n(to apply the gaussian_blur n times)\n\n");
        printf("Use otsu + path-rc + path-dest \n(to binarise the picture)\n\n");
        return 1;
    }

    if(!strcmp(argv[1],"grayscale")){
        if(argc != 4)
            errx(1,"grayscale -> wrong number of argument\n");
        SDL_Surface* image = load(argv[2]);
        image = to_grayscale(image);
        save(image, argv[3]);
        printf("grayscale -> picture saved\n");
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

    if(!strcmp(argv[1],"otsu")){
        if(argc != 4)
            errx(1,"otsu -> wrong number of argument\n");
        SDL_Surface* image = load(argv[2]);
        image = otsu(image);
        save(image, argv[3]);
        printf("otsu -> picture saved\n");
        return 0;
    }

    if(!strcmp(argv[1],"all")){
        if(argc != 4)
            errx(1,"all -> wrong number of argument\n");
        if(!strcmp(argv[2],"-")){
            char s[] = "tests/assets/image_00.jpeg";
            char s1[] = "0.jpeg";
            for(int i = 1; i < 7; i++){
                s[20] = '0'+i;
                s1[0] = '0'+i;
                SDL_Surface* image = load(s);
                image = to_grayscale(image);
                image = otsu(image);

                save(image, s1);
                printf("generate image -> %s\n",s1);
            }
        }
        else{
            SDL_Surface* image = load(argv[2]);
            image = to_grayscale(image);
            //image = gaussian_blur(image, 1);
            //image = simple_blur(image,2);
            image = otsu(image);
            save(image, argv[3]);
            printf("all -> picture saved\n");
            return 0;
        }
        return 0;
    }


    printf("wrong argument\n");
    return 0;
}
