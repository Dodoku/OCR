#include <SDL2/SDL_image.h>
#include <SDL2/SDL_pixels.h>
#include <err.h>
#include "wall_draw.h"
#include "../tools/image.h"


/*
 * Draw the digit for each number in the sudoku
 * @param image (SDL_Surface) : the image on which we display the digits
 * @param x (int) : the x postion of the digit (to left)
 * @param y (int) : the y postion of the digit
 * @param n (int) : the number to display
 * @authur Nicolas Prevost
 */

void display_digit(SDL_Surface *image, int x, int y, int n, SDL_Color color) {
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
            return;
            break;
    }
    for (int i = 0; i < 100; i++)
        for (int j = 0; j < 100; j++)
            if(get_pixel(number, i, j).r<245)
                set_pixel(image, x + i, y + j,color);
}

/*
 * Draw the digit for each number in the sudoku
 * @param sudoku (char *) : the unsolved sudoku
 * @param path (char*) : the solved sudoku
 * return SDL+SDL_Surface
 * @authur Nicolas Prevost
 */

SDL_Surface* generate_digit_picture(char* sudoku, char* solved) {

    int grid[81] = {0};
    int solvedgrid[81] = {0};
    int i=0,i2=0;
    while(sudoku[i]!=0)
    {
        if(sudoku[i]==' '||sudoku[i]=='\n')
        {
            i++;
        }
        else
        {
            if(sudoku[i]=='.')
            {
                grid[i2]=0;
            }
            else
            {
                grid[i2]=sudoku[i]-'0';
            }
            solvedgrid[i2]=solved[i]-'0';
            i2++;
            i++;
        }
    }

    SDL_Surface *image = create_empty(993, 993);

    SDL_Color red=to_color(0,0,255,0);
    SDL_Color black=to_color(0,0,0,0);

    horizontal_wall(image, 0, 12);
    vertical_wall(image, 0, 12, 12);

    int x = 13;
    int y = 12;
    int horizontal = 0;
    int vertical = 0;
    for (int index = 0; index < 81; index++) {
        display_digit(image, x, y, solvedgrid[index],solvedgrid[index]==grid[index]?black:red);
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

    return image;
}
