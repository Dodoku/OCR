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

        char* og="... ..4 58.... 721 ..34.3 ... ...21. .67 ..4.7. ... 2..63. .49 ..13.6 ... ...... 158 ..6... ..6 95.";
        char* sol="127 634 589589 721 643463 985 127218 567 394974 813 265635 249 871356 492 718792 158 436841 376 952";
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
