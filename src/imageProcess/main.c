#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_pixels.h>

#include "../tools/image.h"
#include "rotate.h"
#include "contrast.h"
#include "greyScale.h"

int main() {
    char s[] = "./tests/assets/image_00.jpeg";
    char ooooh[] = "./tests/assets/gray_00.jpeg";
    for(int i = 1; i < 7; i++){
	s[22] = '0'+i;
	ooooh[21] = '0'+i;
	SDL_Surface* image = load(s);
	SDL_Surface* grey = otsu(image);
	save(grey, ooooh);
    }
    return 0;
}
