#include <stdio.h>
#include <SDL2/SDL.h>

#include "image.h"

int main(){
	SDL_Surface* image = load("tests/assets/image_01.jpeg");
    set_pixel(image, 0, 0, to_color(255,255,255,255));
    SDL_Color pixel = get_pixel(image, 0, 0);
    printf("r: %u, g: %u, b: %u, a: %u\n", pixel.r, pixel.g, pixel.b, pixel.a);