#include <stdio.h>
#include <err.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_pixels.h>

#include "../tools/image.h"

SDL_Surface* noise_reduction(SDL_Surface* image){
  SDL_Surface* ret = create_empty(image->w, image->h);
  for (int i = 1; i < image->w-1; i++) {
        for (int j = 1; j < image->h-1; j++) {
            int r=0,g=0,b=0;
            SDL_Color pixel;
            for(int k=0; k<3;k++){
              for(int l=0; l<3; l++){
                pixel = get_pixel(image,i-1+k,j-1+l);
                r+=pixel.r;
                g+=pixel.g;
                b+=pixel.b;
                set_pixel(ret,i,j,to_color(r/9,g/9,b/9,0));
              }
            }
        }
    }
    return ret;
}
