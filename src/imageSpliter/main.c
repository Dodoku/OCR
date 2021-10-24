#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_pixels.h>

#include "hough.h"
#include "../tools/image.h"

int main(int argc, char *argv[]) {
    if(argc != 3){
	printf("failed to split, use the architecture below :\n");
	printf("./build/imageSpliter load_path save_path\n");
	return 1;
    }
    SDL_Surface* input = load(argv[1]);
    SDL_Surface* output = hough_transform(input);
    save(output, argv[2]);
    return 0;
}

/*
int main() {
    SDL_Surface* image = load("tests/assets/imageGrey_01.jpeg");
    hough_transform(image);    
    return 0;
}

void test_matrix(){
    int** A = init_matrice(10,8);
    for (size_t i = 0; i < 10; i++)
        A[i][1] = 1;
    print_matrice(A,10,8);
    free_matrice(A,10);
    return 0;
}

void test_SDL(){
    SDL_Surface* print = create_empty(100, 80);
    for (size_t i = 0; i < 100; i++){
        set_pixel(print, i, 1, to_color(0, 0, 0, 255));
    }
    save(print, "tests/assets/sinus.jpeg");
    return 0;
}
*/
