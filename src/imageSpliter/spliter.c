#include "../tools/image.h"

/*
 * crop the picture at (x1, y1) (x2,y2)
 * @param image (SDL_Surface*) : the picture to crop
 * @param x1,y1 (int) : coordonates at the right top corner
 * @param x2,y2 (int) : coordonates at the bottom left corner
 * @return (SDL_Surface*) : return the splited picture
 * @author Nicolas Prevost
 */

SDL_Surface* split(SDL_Surface* image, int x1, int y1, int x2, int y2)
{
    SDL_Surface* ret = create_empty(x2-x1, y2-y1);
    for(int i=0; i<x2-x1;i++)
    {
        for(int j=0; j<y2-y1;j++)
        {
            set_pixel(ret, i, j, get_pixel(image, x1+i,y1+j));
        }
    }
    return ret;
}
