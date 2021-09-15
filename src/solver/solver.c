#include <stdio.h>
#include <err.h>
#include <stdbool.h>

#define sudoSize 9

/*
 * Initialize the grid from the file
 * @param path (char*) : path of the grid file
 * @param grid (int*) : empty array of sudoku grid
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
 * Prints the grid on the console
 * @param grid (int*) : array of sudoku grid
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

/*
 * Returns true if the given column is solved
 * @param x (int) : index of the column
 * @param grid (int*) : array of sudoku grid
 * @return (bool)
 * @author Valentin Uhlrich
 */
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

/*
 * Returns true if the given line is solved 
 * @param y (int) : index of the line
 * @param grid (int*) : array of sudoku grid
 * @return (bool)
 * @author Valentin Uhlrich
 */
bool is_line_solved(int y, int* grid){
    for(int i = 1; i <= sudoSize; i++){
        bool find = false;
        for(int x = 0; x < sudoSize && !find; x++){
            find = *(grid + y*sudoSize + x) == i;
        }
        if(!find) return false;
    }
    return true;
}

/*
 * Returns true if the 3x3 square containing the given coords is solved
 * @param x (int) : index of the column
 * @param y (int) : index of the line
 * @param grid (int*) : array of sudoku grid
 * @return (bool)
 * @author Valentin Uhlrich
 */
bool is_square_solved(int x, int y, int* grid){
    for(int n = 1; n <= sudoSize; n++){
        bool find = false;

        for(int i = y/3*3; i <= (y/3+1) && !find; i++){
            for(int j = x/3*3; j < (x/3+1)*3 && !find; j++){
                find = *(grid + y*sudoSize + x) == i;
            }
        }
        if(!find) return false;
    }
    return true;
}

