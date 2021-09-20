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
	SDL_Surface* image = create_empty(72, 99);

	horizontal_wall(image,0);
	horizontal_wall(image,1);
	horizontal_wall(image,2);
	vertical_wall(image,0,3);
	vertical_wall(image,1,3);
	vertical_wall(image,2,3);


	int x = 3;
	int y = 3;
	int horizontal = 0;
	int vertical = 0;

	for(int index=0;index<81;index++){
		display_digit(image,x,y,sudoku[index]);
		horizontal++;

		if(horizontal==3 || horizontal==6 || horizontal==9){
			if(horizontal==9){
				vertical_wall(image,x+6,y);
				vertical_wall(image,x+7,y);
				vertical_wall(image,x+8,y);
				x=3;
				vertical++;
				if(vertical==3 || vertical==6 || vertical==9){
					horizontal_wall(image,y+9);
					horizontal_wall(image,y+10);
					horizontal_wall(image,y+11);
					y+=12;
					horizontal=0;
				}
				else{
					horizontal_wall(image,y+9);
					y+=10;
					horizontal=0;
				}
				if(vertical!=9){
					vertical_wall(image,0,y);
				vertical_wall(image,1,y);
				vertical_wall(image,2,y);
				}
			}
			else{
				vertical_wall(image,x+6,y);
				vertical_wall(image,x+7,y);
				vertical_wall(image,x+8,y);
				x+=9;
			}
		}
		else{
			vertical_wall(image,x+6,y);
			x+=7;
		}

		
	}

	save(image, path);
}
