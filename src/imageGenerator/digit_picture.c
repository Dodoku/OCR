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

	horizontal_wall(image,0);
	horizontal_wall(image,1);
	horizontal_wall(image,2);
	vertical_wall(image,0);
	vertical_wall(image,1);
	vertical_wall(image,2);


	int x = 3;
	int y = 3;
	int horizontal = 1;
	int vertical = 1;
	int index = 0;

	for(int index=0;index<81;index++){
		display_digit(image,x,y,sudoku[index]);
		horizontal++;
		if(horizontal%3==0){
			vertical_wall(image,x+6);
			vertical_wall(image,x+7);
			vertical_wall(image,x+8);
			if(horizontal==9){
				vertical++;
				x=3
			}
			else{
				x+=9;
			}
		}
		else{
			vertical_wall(imagex+6)
			x+=7
		}
	}

	save(image, path);
}
