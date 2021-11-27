#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_pixels.h>

#include "spliter.h"
#include "../tools/image.h"
#include "../tools/hough.h"

int main(int argc, char *argv[])
{
    char s[] = "2.jpeg";
    for(int i=1;i<7;i++ )
    {
        s[0]=i+'0';
        SDL_Surface* image = load(s);
        printf(s );
        printf("\n%f\n\n",90-hough_transform(image));
        save(image, s);

        SDL_FreeSurface(image);
    }
    return 0;

}
