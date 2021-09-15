#include <stdio.h>
#include <err.h>
#include <stdbool.h>

#define sudoSize 9

/*
 * Initialize the grid from the file
 * @param path (char*) : path of the grid file
 * @param grid (int*) : array of grid empty
 * @author Valentin Uhlrich
 */
void init_solver(char* path, int* grid){
    FILE* fp;
    char c;

    fp = fopen(path, "r");
    if(!fp) errx(1, "Couldn't open %s\n", path);

    int i = 0;

    while((c=fgetc(fp))!=EOF){
        if(c == '.') *(grid + i) = 0;
        else if(c > '0' && c <= '9')
            *(grid + i) = c - '0';
        else if(c != '\n' && c != '\0' && c != ' ')
            errx(1, "File doesn't respect the format");
        else
            continue;
        i++;
    }
    fclose(fp);
}

/*
 * Print the grid in console
 * @param grid (int*) : array of grid
 * @author Valentin Uhlrich
 */
void print_line(int size);
void print_sudoku(int* grid){
    for (int i = 0; i < sudoSize; i++){
        if(i % 3 == 0) print_line(sudoSize);

        for(int j = 0; j < sudoSize; j++){

            printf(j % 3 == 0 ? "| " : " ");
            printf(*(grid + i*sudoSize + j) == 0 ? 
                    " " : "%i", *(grid + i*sudoSize + j));
        }
        printf("|\n");
    }
    print_line(9);
}
void print_line (int size){
    for(int i = 0; i < size/3; i++){
        printf("-------");
    }
    printf("-\n");
}

bool is_column_solved(int x, int* grid){
    for(int i = 1; i <= sudoSize; i++){
        bool find = false;
        for(int y = 0; y < sudoSize && !find; y++){
            find = *(grid + y*sudoSize + x) == i;
        }
        if(!find) return false;
    }
    return true;
}
