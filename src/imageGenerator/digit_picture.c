#include <SDL2/SDL_image.h>
#include <SDL2/SDL_pixels.h>
#include "digit_draw.h"
#include "wall_draw.h"
#include "../imageProcess/image.h"

void display_digit(SDL_Surface* image, int x, int y, int n){
	switch(n){
		case 1:
			one(image,x,y);
			break;
		case 2:
			two(image,x,y);
			break;
		case 3:
			three(image,x,y);
			break;
		case 4:
			four(image,x,y);
			break;
		case 5:
			five(image,x,y);
			break;
		case 6:
			six(image,x,y);
			break;
		case 7:
			seven(image,x,y);
			break;
		case 8:
			eight(image,x,y);
			break;
		case 9:
			nine(image,x,y);
			break;
		default:
			break;
	}
}

void generate_digit_picture(int sudoku[], char* path[]){
	SDL_Surface* image = create_empty(73, 100);

	int x = 3;
	int y = 3;
	int horizontal = 0;
	int vertical = 0;
	int index = 0;
	horizontal_wall(image,0);
	horizontal_wall(image,1);
	horizontal_wall(image,2);
	horizontal_wall(image,12);
	vertical_wall(image,0);
	vertical_wall(image,1);
	vertical_wall(image,2);
	vertical_wall(image,9);
	vertical_wall(image,16);
	display_digit(image,x,y,1);
	x += 7;
	display_digit(image,x,y,2);
	x += 7;
	display_digit(image,x,y,3);
	y = 13;
	x = 3;
	display_digit(image,x,y,4);
	x += 7;
	display_digit(image,x,y,5);
	char dest[] = "tests/refdturn.jpeg";
	save(image, dest);
}
