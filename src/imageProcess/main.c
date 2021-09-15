#include <SDL.h>
#include <stdio.h>
#include "image.h"

int main(){
	SDL_Surface* picture = load("/home/nicolas/Desktop/OCR/tests/assets/image_01.jpeg");
	if(!picture){
		printf("error in load\n");
	}
	else{
		printf("image loaded succesfully\n");
	}
	return 0;
}
