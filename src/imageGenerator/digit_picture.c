#include <SDL2/SDL_image.h>
#include <SDL2/SDL_pixels.h>
#include "wall_draw.h"
#include "../imageProcess/image.h"

/*
 * Draw the digit for each number in the sudoku
 * @param image (SDL_Surface) : the image on which we display the digits
 * @param x (int) : the x postion of the digit (to left)
 * @param y (int) : the y postion of the digit
 * @param n (int) : the number to display
 * @authur Nicolas Prevost
 */

void display_digit(SDL_Surface *image, int x, int y, int n) {
    SDL_Surface *number;
    switch (n) {
        case 1:
            number = load("src/imageGenerator/assets/one.jpg");
            break;
        case 2:
            number = load("src/imageGenerator/assets/two.jpg");
            break;
        case 3:
            number = load("src/imageGenerator/assets/three.jpg");
            break;
        case 4:
            number = load("src/imageGenerator/assets/four.jpg");
            break;
        case 5:
            number = load("src/imageGenerator/assets/five.jpg");
            break;
        case 6:
            number = load("src/imageGenerator/assets/six.jpg");
            break;
        case 7:
            number = load("src/imageGenerator/assets/seven.jpg");
            break;
        case 8:
            number = load("src/imageGenerator/assets/eight.jpg");
            break;
        case 9:
            number = load("src/imageGenerator/assets/nine.jpg");
            break;
        default:
            break;
    }
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            set_pixel(image, x + i, y + j, get_pixel(number, i, j));
        }
    }
}

/*
 * Draw the digit for each number in the sudoku
 * @param sudoku (int[]) : a 81 int array, that contains the sudoku data
 * @param path (char[]*) : a string that contains the path to save the generated
 * picture
 * @authur Nicolas Prevost
 */

void generate_digit_picture(int sudoku[], char *path[]) {
    SDL_Surface *image = create_empty(993, 993);

    horizontal_wall(image, 0, 12);
    vertical_wall(image, 0, 12, 12);

    int x = 13;
    int y = 12;
    int horizontal = 0;
    int vertical = 0;

    for (int index = 0; index < 81; index++) {
        display_digit(image, x, y, sudoku[index]);
        horizontal++;

        if (horizontal == 3 || horizontal == 6 || horizontal == 9) {
            if (horizontal == 9) {
                vertical_wall(image, x + 101, y, 12);
                x = 13;
                vertical++;
                if (vertical == 3 || vertical == 6 || vertical == 9) {
                    horizontal_wall(image, y + 101, 12);
                    y += 113;
                    horizontal = 0;
                } else {
                    horizontal_wall(image, y + 101, 6);

                    y += 107;
                    horizontal = 0;
                }
                if (vertical != 9) {
                    vertical_wall(image, 0, y, 12);
                }
            } else {
                vertical_wall(image, x + 101, y, 12);
                x += 113;
            }
        } else {
            vertical_wall(image, x + 101, y, 6);
            x += 107;
        }
    }

    save(image, path);
}
