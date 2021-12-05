#include <stdio.h>
#include <err.h>
#include <stdlib.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_pixels.h>

#include "../tools/image.h"

SDL_Color grayscale(SDL_Color color) {
    Uint32 value = (color.r + color.g + color.b)/3;
    return to_color(value, value, value, color.a);
}

/**
 * @brief Convert an image to grayscale
 * /!\ IMAGE IS DESTROYED /!\
 * @param image (SDL_Surface*) The image to convert
 * @return SDL_Surface* grayscale image
 * @author Nicolas Prevost
 */
SDL_Surface* to_grayscale(SDL_Surface* image){
    SDL_Surface *result = create_empty(image->w, image->h);
    for (int i = 0; i < image->w; i++) {
        for (int j = 0; j < image->h; j++) {
            SDL_Color color = get_pixel(image, i, j);
            color = grayscale(color);
            set_pixel(result, i, j, color);
        }
    }
    SDL_FreeSurface(image);
    return result;
}

void otsu_histogram(SDL_Surface* image, int* A){
    size_t height = image->h, width = image->w;
    for(size_t i = 0; i < width; i++){
        for(size_t j = 0; j < height; j++){
            SDL_Color color = get_pixel(image, i, j);
            A[color.r] += 1;
        }
    }
}

int otsu_threshold(int* A, int N){
    double threshold = 0, var_max = 0, sum = 0, sumB = 0;
    double q1 = 0, q2 = 0, u1 = 0, u2 = 0, u, o;
    for(size_t i = 0; i <= 255; i++)
        sum += i * A[i];
    for(size_t t = 0; t <= 255; t++){
        q1 += A[t];
        if (q1 == 0)
            continue;
        q2 = N - q1;
        sumB += t*A[t];
        u1 = sumB/q1;
        u2 = (sum - sumB)/q2;
        u = u1-u2;
        o = q1*q2*u*u;
        if(o > var_max){
            threshold = t;
            var_max = o;
        }
    }
    return (int) threshold;
}

int test_proportions(SDL_Surface* image){
    int sum = 0;
    for(int i = 0; i < image->w/10; i++){
        for(int j = 0; j < image->h/10; j++){
            if(get_pixel(image, i, j).r >= 255/2)
                sum++;
        }
    }
    return (double) sum / (image->w/100 * image->h/100) < 0.05;
}

void otsu_transform(SDL_Surface* image, int decallage){
    const SDL_Color black = to_color(0,0,0,255);
    const SDL_Color white = to_color(255,255,255,255);

    size_t height = image->h, width = image->w;
    int A[256];
    for(size_t i = 0; i < 256; i++)
        A[i] = 0;

    otsu_histogram(image, A);

    int threshold = otsu_threshold(A, height*width);
    for(size_t i = 0; i < width; i++){
        for(size_t j = 0; j < height; j++){
            if(get_pixel(image, i, j).r > threshold - decallage*2)
                set_pixel(image, i, j, black);
            else
                set_pixel(image, i, j, white);
        }
    }
}

SDL_Surface* otsu(SDL_Surface* input, int decallage)
{
    SDL_Surface* output = to_grayscale(input);
    otsu_transform(output, decallage);
    return output;
}

int check(int x, int max)
{
    if(x<0)
        return 0;
    if(x>=max)
        return max-1;
    return x;
}

SDL_Surface* adaptative_treashold(SDL_Surface* image)
{
    int w=image->w;
    int h=image->h;
    int s=w/8;
    int t=15;
    long* intImg=calloc(h*w,sizeof(long));

    SDL_Surface* out = create_empty(w,h);

    int sum=0;
    for(int i=0;i<w;i++)
    {
        for(int j=0;j<h;j++)
        {
            sum+=get_pixel(image,i,j).r;
            if(i==0)
            {
                intImg[i*h+j]=sum;
            }
            else
            {
                intImg[i*h+j]=intImg[(i-1)*h+j]+sum;
            }
        }
    }

    int x1,x2,y1,y2,count;
    for(int i=0;i<w;i++)
    {
        for(int j=0;j<h;j++)
        {
            x1=check(i-s/2,w);
            x2=check(i+s/2,w);
            y1=check(j-s/2,h);
            y2=check(j+s/2,h);
            count=(x2-x1)*(y2-y1);
            sum=intImg[check(x2,w)*h+check(y2,h)]-intImg[check(x2,w)*h+check(y1-1,h)]-intImg[check(x1-1,w)*h+check(y2,h)]+intImg[check(x1-1,w)*h+check(y1-1,h)];
            if(get_pixel(image,i,j).r*count <= (sum*(100-t)/100))
            {
                set_pixel(out,i,j,to_color(255,255,255,255));
            }
            else
            {
                set_pixel(out,i,j,to_color(0,0,0,255));
            }
        }
    }
    return out;
}
