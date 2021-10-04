#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "solver.h"

int main(int argc, char **argv){
    int grid[9*9] = { 0 };
    if(argc < 2){
        printf("Error: missing path argument\n");
        return EXIT_FAILURE;
    }

    init_grid(argv[1], grid);

    solve(grid);

    char *out = argv[1];
    strcat(out, ".out");
    save_grid(out, grid);

    printf("Sudoku solved and saved to \"%s\"\n", out);
    return EXIT_SUCCESS;
}
