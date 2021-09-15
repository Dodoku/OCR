#include <SDL.h>
#include <stdio.h>
#include "image.h"

//picture path "/home/nicolas/Desktop/OCR/tests/assets/image_02.jpeg"

int main(){
	SDL_Surface* picture = load("tests/assets/image_02.jpeg");
	if(!picture){
		printf("error in load\n");
	}
	else{
		printf("picture loaded succefully!\n");
	}


	printf("\nlargeur:%d hauteur:%d\n", picture->w, picture->h);
	return 0;
}
