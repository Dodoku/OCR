#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_pixels.h>

#include "../tools/image.h"
#include "rotate.h"
#include "contrast.h"
#include "greyScale.h"
#include "noise_reduction.h"

int main() {
  SDL_Surface* image = load("./tests/assets/image_04.jpeg");
  save(image, "generate.jpeg");
  for(int i = 0; i < 10; i++){
    image = noise_reduction(image,0.8);
  }


  save(image, "generate1.jpeg");
  image = to_black_and_white(image);
  save(image, "generate2.jpeg");

  return 0;
}
