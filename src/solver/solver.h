#include <stdbool.h>

#ifndef SOLVER_DEF
#define SOLVER_DEF

void init_grid(char *path, int *grid);
void save_grid(char *path, int *grid);
void print_grid(int *grid);

void solve(int *grid);

#endif
