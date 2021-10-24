#include "../tools/image.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_pixels.h>

/*
 * Draw a horizontal wall for the sudoku grid
 * @param iamge (SDL_Surface) : the image on which we draw the wall
 * @param y (int) : the y postion of the wall (top left)
 * @param thickness (int) : the thickness of the wall
 * @authur Prevost Nicolas
 */
void horizontal_wall(SDL_Surface *image, int y, int thickness) {
    for (int i = 0; i <= 993; i++) {
        for (int t = 0; t < thickness; t++) {
            set_pixel(image, i, y + t, to_color(0, 0, 0, 0));
        }
    }
}

/*
 * Draw a horizontal wall for the sudoku grid
 * @param iamge (SDL_Surface) : the image on which we draw the wall
 * @param x (int) : the x postion of the wall (top left)
 * @param y (int) : the y postion of the wall
 * @param thickness (int) : the thickness of the wall
 * @authur Prevost Nicolas
 */
void vertical_wall(SDL_Surface *image, int x, int y, int thickness) {
    for (int i = 0; i <= 100; i++) {
        for (int t = 0; t < thickness; t++) {
            set_pixel(image, x + t, i + y, to_color(0, 0, 0, 0));
        }
    }
}