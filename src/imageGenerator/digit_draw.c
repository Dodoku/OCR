#include "../imageProcess/image.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_pixels.h>

void one(SDL_Surface* image, int x, int y){
	set_pixel(image,x+3,y+1,to_color(0,0,0,255));
	set_pixel(image,x+2,y+2,to_color(0,0,0,255));
	set_pixel(image,x+1,y+3,to_color(0,0,0,255));
	set_pixel(image,x+3,y+2,to_color(0,0,0,255));
	set_pixel(image,x+3,y+3,to_color(0,0,0,255));
	set_pixel(image,x+3,y+4,to_color(0,0,0,255));
	set_pixel(image,x+3,y+5,to_color(0,0,0,255));
	set_pixel(image,x+3,y+6,to_color(0,0,0,255));
	set_pixel(image,x+3,y+7,to_color(0,0,0,255));
	set_pixel(image,x+2,y+7,to_color(0,0,0,255));
	set_pixel(image,x+4,y+7,to_color(0,0,0,255));
}

void two(SDL_Surface* image, int x, int y){
	set_pixel(image,x+2,y+1,to_color(0,0,0,255));
	set_pixel(image,x+1,y+2,to_color(0,0,0,255));
	set_pixel(image,x+3,y+1,to_color(0,0,0,255));
	set_pixel(image,x+4,y+2,to_color(0,0,0,255));
	set_pixel(image,x+4,y+3,to_color(0,0,0,255));
	set_pixel(image,x+3,y+4,to_color(0,0,0,255));
	set_pixel(image,x+2,y+5,to_color(0,0,0,255));
	set_pixel(image,x+1,y+6,to_color(0,0,0,255));
	set_pixel(image,x+1,y+7,to_color(0,0,0,255));
	set_pixel(image,x+2,y+7,to_color(0,0,0,255));
	set_pixel(image,x+3,y+7,to_color(0,0,0,255));
	set_pixel(image,x+4,y+7,to_color(0,0,0,255));
}
void three(SDL_Surface* image, int x, int y){
	set_pixel(image,x+2,y+1,to_color(0,0,0,255));
	set_pixel(image,x+1,y+2,to_color(0,0,0,255));
	set_pixel(image,x+3,y+1,to_color(0,0,0,255));
	set_pixel(image,x+4,y+2,to_color(0,0,0,255));
	set_pixel(image,x+4,y+3,to_color(0,0,0,255));
	set_pixel(image,x+3,y+4,to_color(0,0,0,255));
	set_pixel(image,x+4,y+5,to_color(0,0,0,255));
	set_pixel(image,x+4,y+6,to_color(0,0,0,255));
	set_pixel(image,x+3,y+7,to_color(0,0,0,255));
	set_pixel(image,x+2,y+7,to_color(0,0,0,255));
	set_pixel(image,x+1,y+6,to_color(0,0,0,255));
}
void four(SDL_Surface* image, int x, int y){
	set_pixel(image,x+1,y+1,to_color(0,0,0,255));
	set_pixel(image,x+1,y+2,to_color(0,0,0,255));
	set_pixel(image,x+1,y+3,to_color(0,0,0,255));
	set_pixel(image,x+1,y+4,to_color(0,0,0,255));
	set_pixel(image,x+4,y+1,to_color(0,0,0,255));
	set_pixel(image,x+4,y+2,to_color(0,0,0,255));
	set_pixel(image,x+4,y+3,to_color(0,0,0,255));
	set_pixel(image,x+4,y+4,to_color(0,0,0,255));
	set_pixel(image,x+3,y+4,to_color(0,0,0,255));
	set_pixel(image,x+2,y+4,to_color(0,0,0,255));
	set_pixel(image,x+4,y+5,to_color(0,0,0,255));
	set_pixel(image,x+4,y+6,to_color(0,0,0,255));
	set_pixel(image,x+4,y+7,to_color(0,0,0,255));

}
void five(SDL_Surface* image, int x, int y){
	set_pixel(image,x+1,y+1,to_color(0,0,0,255));
	set_pixel(image,x+2,y+1,to_color(0,0,0,255));
	set_pixel(image,x+3,y+1,to_color(0,0,0,255));
	set_pixel(image,x+4,y+1,to_color(0,0,0,255));
	set_pixel(image,x+1,y+2,to_color(0,0,0,255));
	set_pixel(image,x+1,y+3,to_color(0,0,0,255));
	set_pixel(image,x+2,y+3,to_color(0,0,0,255));
	set_pixel(image,x+3,y+3,to_color(0,0,0,255));
	set_pixel(image,x+4,y+4,to_color(0,0,0,255));
	set_pixel(image,x+4,y+5,to_color(0,0,0,255));
	set_pixel(image,x+4,y+6,to_color(0,0,0,255));
	set_pixel(image,x+3,y+7,to_color(0,0,0,255));
	set_pixel(image,x+2,y+7,to_color(0,0,0,255));
	set_pixel(image,x+1,y+6,to_color(0,0,0,255));

}
void six(SDL_Surface* image, int x, int y){
	set_pixel(image,x+1,y+2,to_color(0,0,0,255));
	set_pixel(image,x+2,y+1,to_color(0,0,0,255));
	set_pixel(image,x+3,y+1,to_color(0,0,0,255));
	set_pixel(image,x+4,y+2,to_color(0,0,0,255));
	set_pixel(image,x+1,y+3,to_color(0,0,0,255));
	set_pixel(image,x+1,y+4,to_color(0,0,0,255));
	set_pixel(image,x+1,y+5,to_color(0,0,0,255));
	set_pixel(image,x+1,y+6,to_color(0,0,0,255));
	set_pixel(image,x+2,y+7,to_color(0,0,0,255));
	set_pixel(image,x+3,y+7,to_color(0,0,0,255));
	set_pixel(image,x+4,y+6,to_color(0,0,0,255));
	set_pixel(image,x+4,y+5,to_color(0,0,0,255));
	set_pixel(image,x+3,y+4,to_color(0,0,0,255));
	set_pixel(image,x+2,y+4,to_color(0,0,0,255));

}
void seven(SDL_Surface* image, int x, int y){
	set_pixel(image,x+1,y+1,to_color(0,0,0,255));
	set_pixel(image,x+2,y+1,to_color(0,0,0,255));
	set_pixel(image,x+3,y+1,to_color(0,0,0,255));
	set_pixel(image,x+4,y+1,to_color(0,0,0,255));
	set_pixel(image,x+4,y+2,to_color(0,0,0,255));
	set_pixel(image,x+4,y+3,to_color(0,0,0,255));
	set_pixel(image,x+3,y+4,to_color(0,0,0,255));
	set_pixel(image,x+3,y+5,to_color(0,0,0,255));
	set_pixel(image,x+2,y+6,to_color(0,0,0,255));
	set_pixel(image,x+2,y+7,to_color(0,0,0,255));

}
void eight(SDL_Surface* image, int x, int y){
	set_pixel(image,x+2,y+1,to_color(0,0,0,255));
	set_pixel(image,x+1,y+2,to_color(0,0,0,255));
	set_pixel(image,x+3,y+1,to_color(0,0,0,255));
	set_pixel(image,x+4,y+2,to_color(0,0,0,255));
	set_pixel(image,x+4,y+3,to_color(0,0,0,255));
	set_pixel(image,x+3,y+4,to_color(0,0,0,255));
	set_pixel(image,x+4,y+5,to_color(0,0,0,255));
	set_pixel(image,x+4,y+6,to_color(0,0,0,255));
	set_pixel(image,x+3,y+7,to_color(0,0,0,255));
	set_pixel(image,x+2,y+7,to_color(0,0,0,255));
	set_pixel(image,x+1,y+6,to_color(0,0,0,255));
	set_pixel(image,x+1,y+3,to_color(0,0,0,255));
	set_pixel(image,x+2,y+4,to_color(0,0,0,255));
	set_pixel(image,x+1,y+5,to_color(0,0,0,255));
	set_pixel(image,x+1,y+6,to_color(0,0,0,255));

}
void nine(SDL_Surface* image, int x, int y){
	set_pixel(image,x+2,y+1,to_color(0,0,0,255));
	set_pixel(image,x+1,y+2,to_color(0,0,0,255));
	set_pixel(image,x+3,y+1,to_color(0,0,0,255));
	set_pixel(image,x+4,y+2,to_color(0,0,0,255));
	set_pixel(image,x+4,y+3,to_color(0,0,0,255));

	set_pixel(image,x+4,y+4,to_color(0,0,0,255));

	set_pixel(image,x+3,y+4,to_color(0,0,0,255));
	set_pixel(image,x+4,y+5,to_color(0,0,0,255));
	set_pixel(image,x+4,y+6,to_color(0,0,0,255));
	set_pixel(image,x+3,y+7,to_color(0,0,0,255));
	set_pixel(image,x+2,y+7,to_color(0,0,0,255));
	set_pixel(image,x+1,y+6,to_color(0,0,0,255));
	set_pixel(image,x+1,y+3,to_color(0,0,0,255));
	set_pixel(image,x+2,y+4,to_color(0,0,0,255));
}

