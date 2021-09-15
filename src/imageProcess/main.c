#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_pixels.h>

#include "image.h"
#include "rotate.h"
#include "contrast.h"

int main(){
	double x = 2.5;
	SDL_Surface* image = load("tests/assets/image_01.jpeg");
	save(contrast(image,x), "tests/assets/image_011.jpeg");

	image = load("tests/assets/image_02.jpeg");
	save(contrast(image,x), "tests/assets/image_022.jpeg");

	image = load("tests/assets/image_03.jpeg");
	save(contrast(image,x), "tests/assets/image_033.jpeg");

	image = load("tests/assets/image_04.jpeg");
	save(contrast(image,x), "tests/assets/image_044.jpeg");

	image = load("tests/assets/image_05.jpeg");
	save(contrast(image,x), "tests/assets/image_055.jpeg");

	image = load("tests/assets/image_06.jpeg");
	save(contrast(image,x), "tests/assets/image_066.jpeg");
}
