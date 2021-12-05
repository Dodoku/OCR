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
        for(int j=0; j<y2-y1;j++)
            set_pixel(ret, i, j, get_pixel(image, x1+i,y1+j));
    return ret;
}

/*
 * return a pic_pos for the network
 * @param image (SDL_Surface*) : the image to split
 * @param x1,y1 (int) : coordonates at the right top corner
 * @param x2,y2 (int) : coordonates at the bottom left corner
 * @return (pic_pos*) : return the struct
 * @author Nicolas Prevost
 */

struct pic_pos* to_network(SDL_Surface* image, int* x1, int* y1, int* x2, int* y2)
{
    struct pic_pos* ret = malloc(sizeof(struct pic_pos)*81);
    if(!ret)
        printf("malloc error\n");
    for(int i=0;i<81;i++)
    {
        struct pic_pos current = {resize(split(image,x1[i],y1[i],x2[i],y2[i]),28,28),x1[i],y1[i],x2[i],y2[i]};
        ret[i]=current;
    }
    return ret;
}

void insert_picture(SDL_Surface* image, int x1, int y1, int x2, int y2, int n)
{
    char path[]="src/assets/0.jpg";
    path[11]=n+'0';
    SDL_Surface* number = load(path);
    number = resize(number,x2-x1,y2-y1);
    save(number,"number.jpg");
    for(int i=0;i<number->w;i++)
    {
        for(int j=0;j<number->h;j++)
        {
            if(get_pixel(number,i,j).r==0)
            {
                set_pixel(image,x1+i,y1+j,to_color(0,0,0,0));
            }
        }
    }
}
