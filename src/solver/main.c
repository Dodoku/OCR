#include<stdbool.h>

#include <stdio.h>
#include "solver.h"

int main(){
    int grid[9*9] = { 0 };
    init_grid("tests/solver/grid_01", grid);
    print_grid(grid);
    solve(grid);
    print_grid(grid);
    printf("%i", is_square_solved(0, 0, grid));
    return 0;
}
