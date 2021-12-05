#include <stdio.h>
#include "digit_picture.h"
#include <string.h>
#include "../tools/image.h"

void init_grid(char *path, int *grid) {
    FILE *fp;
    char c;

    fp = fopen(path, "r");
    if (!fp)
        errx(1, "Couldn't open %s\n", path);

    int i = 0;

    while ((c = fgetc(fp)) != EOF) {
        if (c == '.')
            *(grid + i) = 0;
        else if (c > '0' && c <= '9')
            *(grid + i) = c - '0';
        else if (c != '\n' && c != '\0' && c != ' ')
            errx(1, "File doesn't respect the format");
        else
            continue;
        i++;
    }
    fclose(fp);
}





int main(int argc, char *argv[]) {
    if(argc == 1)
    {
        printf("Use generate_digit_picture + sudoku's_path\n");
        printf("Use generate_digit_picture + sudoku's_path + sudoku solved path\n");
        return 0;
    }
    if(argc == 2)
    {


        int* sudoku = malloc(sizeof(int)*82);
        init_grid(argv[1],sudoku);

        char out[2048];
        strcpy(out, argv[1]);
        strcat(out, ".jpeg");

        SDL_Surface* image = generate_digit_picture(sudoku, sudoku);
        save(image,out);
        printf("Picture generated and saved as \"%s\"\n", out);
        return 0;
    }
    if(argc == 2)
    {
        int* sudoku = malloc(sizeof(int)*82);
        init_grid(argv[1],sudoku);

        int* solved = malloc(sizeof(int)*82);
        init_grid(argv[2],solved);

        char out[2048];
        strcpy(out, argv[1]);
        strcat(out, ".jpeg");

        SDL_Surface* image = generate_digit_picture(sudoku, solved);
        save(image,out);
        printf("Picture generated and saved as \"%s\"\n", out);
        return 0;
    }

    printf("wrong argument number\n");
    return 1;
}
