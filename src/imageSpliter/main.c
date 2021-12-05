#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_pixels.h>

#include "spliter.h"
#include "../tools/image.h"
#include "../tools/hough.h"

int main(int argc, char *argv[])
{
    int* x1=malloc(sizeof(int)*81);
    int* x2=malloc(sizeof(int)*81);
    int* y1=malloc(sizeof(int)*81);
    int* y2=malloc(sizeof(int)*81);
    little_square(0,0,100,100,x1,y1,x2,y2);
    for(int i=0;i<81;i++)
    {
        printf("%d %d = %d %d \n",x1[i],y1[i],x2[i],y2[i] );
    }

}
