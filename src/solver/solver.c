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

/*
 * Save the grid in the file
 * @param path (char*) : path of the out file
 * @param grid (int*) : array of the sudoku grid that will be saved
 * @author Valentin Uhlrich
 */
void save_grid(char *path, int *grid) {
    FILE *fp;

    fp = fopen(path, "w");

    for (int y = 0; y < sudoSize; y++) {
        if (y != 0 && y % 3 == 0)
            fputs("\n", fp);

        for (int x = 0; x < sudoSize; x++) {
            if (x != 0 && x % 3 == 0)
                fputs(" ", fp);

            fprintf(fp, "%i", *(grid + y * sudoSize + x));
        }
        fputs("\n", fp);
    }

    fclose(fp);
}

/*
 * Prints the grid on the console
 * @param grid (int*) : array of sudoku grid
 * @author Valentin Uhlrich
 */
void print_line(int size);
void print_grid(int *grid) {
    for (int i = 0; i < sudoSize; i++) {
        if (i % 3 == 0)
            print_line(sudoSize);

        for (int j = 0; j < sudoSize; j++) {
            printf(j % 3 == 0 ? "| " : " ");
            printf(*(grid + i * sudoSize + j) == 0 ? " " : "%i",
                   *(grid + i * sudoSize + j));
        }
        printf("|\n");
    }
    print_line(9);
}
void print_line(int size) {
    for (int i = 0; i < size / 3; i++) {
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
bool is_column_solved(int x, int *grid) {
    for (int i = 1; i <= sudoSize; i++) {
        bool found = false;
        for (int y = 0; y < sudoSize && !found; y++) {
            found = *(grid + y * sudoSize + x) == i;
        }
        if (!found)
            return false;
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
bool is_line_solved(int y, int *grid) {
    for (int i = 1; i <= sudoSize; i++) {
        bool found = false;
        for (int x = 0; x < sudoSize && !found; x++) {
            found = *(grid + y * sudoSize + x) == i;
        }
        if (!found)
            return false;
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
bool is_square_solved(int x, int y, int *grid) {
    x /= 3;
    y /= 3;

    for (int i = 1; i <= sudoSize; i++) {
        bool found = false;
        for (int Y = 0; !found && Y < 3; Y++) {
            for (int X = 0; !found && X < 3; X++) {
                found = *(grid + (Y + y * 3) * sudoSize + (X + x * 3)) == i;
            }
        }

        if (found)
            return false;
    }

    return true;
}

/*
 * Returns true the grid is solved
 * @param grid (int*) : array of sudoku grid
 * @return (bool)
 * @author Valentin Uhlrich
 */
bool is_solved(int *grid) {
    bool square, line, column;
    for (int i = 0; i < sudoSize; i++) {
        square = is_square_solved(i / 3, i % 3, grid);
        line = is_line_solved(i, grid);
        column = is_column_solved(i, grid);
        if (!square || !line || !column)
            return false;
    }
    return true;
}

/*
 * Returns true if the given column already contains the given value
 * @param x (int) : index of the column
 * @param val (int) : value that must be checked
 * @param grid (int*) : array of sudoku grid
 * @return (bool)
 * @author Valentin Uhlrich
 */
bool already_in_column(int x, int val, int *grid) {
    for (int y = 0; y < sudoSize; y++) {
        if (*(grid + y * sudoSize + x) == val)
            return true;
    }
    return false;
}

/*
 * Returns true if the given line already contains the given value
 * @param y (int) : index of the line
 * @param val (int) : value that must be checked
 * @param grid (int*) : array of sudoku grid
 * @return (bool)
 * @author Valentin Uhlrich
 */
bool already_in_line(int y, int val, int *grid) {
    for (int x = 0; x < sudoSize; x++) {
        if (*(grid + y * sudoSize + x) == val)
            return true;
    }
    return false;
}

/*
 * Returns true if the 3x3 square containing the given already contains the
 * given value
 * @param x (int) : index of the column
 * @param y (int) : index of the line
 * @param val (int) : value that must be checked
 * @param grid (int*) : array of sudoku grid
 * @return (bool)
 * @author Valentin Uhlrich
 */
bool already_in_square(int x, int y, int val, int *grid) {
    x /= 3;
    y /= 3;

    for (int Y = 0; Y < 3; Y++) {
        for (int X = 0; X < 3; X++) {
            if (*(grid + (Y + y * 3) * sudoSize + (X + x * 3)) == val)
                return true;
        }
    }
    return false;
}

/*
 * Returns true if the grid is solved
 * @param x (int) : index of the column
 * @param y (int) : index of the lien
 * @param grid (int*) : array of sudoku grid
 * @return (bool)
 * @author Valentin Uhlrich
 */
bool solve_rec(int x, int y, int *grid) {
    if (*(grid + y * sudoSize + x) != 0) {
        return solve_rec(x < 8 ? x + 1 : 0, x < 8 ? y : y + 1, grid);
    }
    int i = 1;
    while (i <= 9) {
        bool valid = !already_in_column(x, i, grid)
                     && !already_in_line(y, i, grid)
                     && !already_in_square(x, y, i, grid);
        *(grid + y * sudoSize + x) = i;
        if (valid) {
            if ((x + 1) * (y + 1) >= 9 * 9)
                return true;
            valid = solve_rec(x < 8 ? x + 1 : 0, x < 8 ? y : y + 1, grid);
            if (valid)
                return true;
        }
        *(grid + y * sudoSize + x) = 0;
        i++;
    }
    return false;
}

/*
 * Try to solve sudoku
 * @param grid (int*) : array of sudoku grid
 * @author Valentin Uhlrich
 */
void solve(int *grid) {
    if (is_solved(grid))
        return;
    solve_rec(0, 0, grid);
}
