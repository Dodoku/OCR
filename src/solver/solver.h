#include <stdbool.h>

#ifndef SOLVER_DEF
#define SOLVER_DEF

void init_grid(char *path, int *grid);
void save_grid(char *path, int *grid);
void print_grid(int *grid);

void init_grid_with_string(char* str, int* grid);
void save_grid_in_string(char str[82], int *grid);

void solve(int *grid);

#endif
