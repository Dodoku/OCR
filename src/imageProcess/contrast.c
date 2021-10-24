#include <err.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_pixels.h>

#include "../tools/image.h"


int truncate(int x){
  if(x < 0)
    return 0;
  if(x > 255)
    return 255;
  return x;
}

/*
 * What the function does
 * @param image (SDL_Surface*) : the picture to contrast
 * @param rate (double) : tell by how much contrast
 * @return (SDL_Surface*) : return the treated picture
 * @authur Nicolas Prevost
 */

SDL_Surface *contrast(SDL_Surface *image) {
    SDL_Surface *ret = create_empty(image->w, image->h);
    SDL_Color current;
    SDL_Color new;
    int contrast = 128;
    int factor = factor = (259 * (contrast + 255)) / (255 * (259 - contrast));
    for (int i = 0; i < image->w; i++) {
        for (int j = 0; j < image->h; j++) {
            current = get_pixel(image, i, j);
            //             Truncate(factor * (currne.r – 128) + 128)
            new = to_color(truncate(factor * (current.r - 128) + 128),
                           truncate(factor * (current.g - 128) + 128),
                           truncate(factor * (current.b - 128) + 128),
                           255);
            set_pixel(ret, i, j, new);
        }
    }
    return ret;
}
