#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_pixels.h>

#include "image.h"

int main(){
	SDL_Surface* image = load("tests/assets/image_01.jpeg");
    SDL_Surface* ret = create_empty(image->w,image->h);
    for(int i=0; i< image->w; i++){
        for(int j=0; j< image->h; j++){
            set_pixel(ret, image->w - i,j, get_pixel(image,i,j));
        }
    }


    IMG_SaveJPG(ret, "tests/assets/returnPicture.jpeg", 100);
}
