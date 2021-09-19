#include "../imageProcess/image.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_pixels.h>

void horizontal_wall(SDL_Surface* image,int y){
	for(int i=0;i<73;i++){
		set_pixel(image, i,y,to_color(100,100,100,255));
	}
}

void vertical_wall(SDL_Surface* image, int x){
	for(int i=0;i<9;i++){
		set_pixel(image, x,i,to_color(100,100,100,255));
	}
}