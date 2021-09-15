#include <stdio.h>
#include "solver.h"

int main(){
    int grid[9*9*9] = { 0 };
    init_solver("tests/solver/grid_01", grid);
    print_sudoku(grid);
    return 0;
}
