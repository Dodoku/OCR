#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_pixels.h>

#include "hough.h"
#include "spliter.h"
#include "../tools/image.h"

int main(int argc, char *argv[])
{
    char s[] = "tests/assets/image_01.jpeg";
    SDL_Surface* image = load(s);
    SDL_Surface* ret;
    ret = split(image,333,333,666,666);
    ret = resize(ret,50,50);

    save(ret, "splited.jpeg");
    printf("image saved");

    return 0;
}
