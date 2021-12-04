#include <stdio.h>
#include "digit_picture.h"
#include <string.h>
#include "../tools/image.h"

int main(int argc, char *argv[]) {
    if(argc == 1){
        printf("Use generate_digit_picture + sudoku's_path(save the sudoku at the given path)\n");
    }
    if(argc == 2){

        char out[2048];

        char og[81]="....458....721..34.3......21..67..4.7....2..63..49..13.6.........158..6.....695.";
        char sol[81]="27634589589721643463985127218567394974813265635249871356492718792158436841376952";
        strcpy(out, argv[1]);
        strcat(out, ".jpeg");

        SDL_Surface* image = generate_digit_picture(og, sol);
        save(image,out);
        printf("Picture generated and saved as \"%s\"\n", out);
    }
    else{
        printf("wrong argument number\n");
    }
    return 0;
}
