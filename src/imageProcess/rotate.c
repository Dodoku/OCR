#include <math.h>

#include "image.h"
#include "rotate.h"

/*
 * What the function does
 * @param image (SDL_Surface*) : the picture to rotate
 * @param angle (int) : gives the angle to rotate
 * @return (SDL_Surface*) : return the rotated picture
 * @authur Nicolas Prevost
 */
SDL_Surface *rotate(SDL_Surface *image, int angle) {
    int width = image->w;
    int height = image->h;

    SDL_Surface *ret = create_empty(image->w, image->h);

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            int hwidth = width / 2;
            int hheight = height / 2;

            int xt = x - hwidth;
            int yt = y - hheight;

            double sinma = sin(-angle);
            double cosma = cos(-angle);

            int xs = (int) round((cosma * xt - sinma * yt) + hwidth);
            int ys = (int) round((sinma * xt + cosma * yt) + hheight);

            if (xs >= 0 && xs < width && ys >= 0 && ys < height) {
                /* set target pixel (x,y) to color at (xs,ys) */
                set_pixel(ret, x, y, get_pixel(image, xs, ys));
            } else {
                /* set target pixel (x,y) to some default background */
                set_pixel(ret, x, y, to_color(0, 0, 0, 0));
            }
        }
    }
    return ret;
}