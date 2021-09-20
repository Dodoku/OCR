#include "../imageProcess/image.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_pixels.h>

void horizontal_wall(SDL_Surface* image,int y, int thickness){
	for(int i=0;i<=993;i++){
		for(int t=0;t<thickness;t++){
			set_pixel(image, i,y+t,to_color(0,0,0,0));
		}
		
	}
}

void vertical_wall(SDL_Surface* image, int x, int y, int thickness){
	for(int i=0;i<=100;i++){
		for(int t=0;t<thickness;t++){
			set_pixel(image, x+t,i+y,to_color(0,0,0,0));
		}
	}
}