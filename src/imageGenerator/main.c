#include <stdio.h>
#include "digit_picture.h"
#include <string.h>

int main(int argc, char *argv[]) {
    if(argc == 1){
        printf("Use generate_digit_picture + sudoku's_path(save the sudoku at the given path)\n");
    }
    if(argc == 2){

        char out[2048];
        strcpy(out, argv[1]);
        strcat(out, ".jpeg");

        generate_digit_picture(argv[1], out);
        printf("Picture generated and saved as \"%s\"\n", out);
    }
    else{
        printf("wrong argument number\n");
    }
    return 0;
}
