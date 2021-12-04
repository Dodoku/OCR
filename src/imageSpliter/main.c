#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_pixels.h>

#include "spliter.h"
#include "../tools/image.h"
#include "../tools/hough.h"

int main(int argc, char *argv[])
{
    SDL_Surface* image = load("tests/assets/image_01.jpeg");
    insert_picture(image, 5,5,150,150,4);
    save(image, "out.jpeg");

    SDL_FreeSurface(image);
    return 0;

}
