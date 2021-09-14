#include <SDL.h>
#include <stdio.h>

int main(){
	SDL_Window *window = NULL;
	if(SDL_Init(SDL_INIT_VIDEO) != 0){
		SDL_Log("init error%s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	window = SDL_CreateWindow("ma fenetre", SDL_WINDOWPOS_CENTERED,
				SDL_WINDOWPOS_CENTERED, 800, 600, 0);

	if(window != NULL){
		SDL_Log("window inti error%s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	SDL_Delay(3000);

	SDL_Quit();
	return 0;
}
