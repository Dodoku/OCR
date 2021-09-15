#include <err.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_pixels.h>

#include "image.h"

//rise the contraste of the given picture
SDL_Surface* contrast(SDL_Surface* image, double rate){

	SDL_Surface* ret = create_empty(image->w, image->h);
	SDL_Color current;
	SDL_Color new;

	for(int i = 0; i < image->w;i++){
		for(int j = 0; j < image->h;j++){
			current = get_pixel(image, i, j);
			if((current.r + current.g + current.b)/3 > 128){
				new = to_color(current.r + (255 - current.r)/rate,
				current.g + (255 - current.g)/rate,
				current.b + (255 - current.b)/rate,
				current.a );
			}
			else{
				new = to_color(current.r / rate,
				current.g / rate,
				current.b / rate,
				current.a);
			}
			set_pixel(ret, i, j, new);
		}
	}
	return ret;
}