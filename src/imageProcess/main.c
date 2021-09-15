#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_pixels.h>

#include "image.h"
#include "rotate.h"
#include "contrast.h"
#include "greyScale.h"

int main(){
	double x = 2.5;

	image = load("tests/assets/image_06.jpeg");
	image = to_black_and_white(image);
	save(contrast(image,x), "tests/assets/image_066.jpeg");
}
