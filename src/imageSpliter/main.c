#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_pixels.h>

#include "hough.h"
#include "../tools/image.h"

int main(int argc, char *argv[])
{
    char s[] = "tests/assets/image_00.jpeg";
    char s1[] = "0.jpeg";
    for(int i = 1; i < 7; i++)
    {
        s[20] = '0'+i;
        s1[0] = '0'+i;
        SDL_Surface* image = load(s);
        image = to_grayscale(image);
        image = otsu(image);

        save(image, s1);
        printf("generate image -> %s\n",s1);
    }
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
