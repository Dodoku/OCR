#ifndef SPLITER_H
#define SPLITER_H

SDL_Surface* split(SDL_Surface* image, int x1, int y1, int x2, int y2);

struct pic_pos* to_network(SDL_Surface* image, int* x1, int* y1, int* x2, int* y2);

void insert_picture(SDL_Surface* image, int x1, int y1, int x2, int y2, int n);

void little_square(int X1, int Y1, int X2, int Y2, int* x1, int* y1, int* x2, int* y2);

#endif
