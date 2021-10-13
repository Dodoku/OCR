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
  image = noise_reduction(image);
  image = noise_reduction(image);
  image = noise_reduction(image);
  image = noise_reduction(image);
  save(image, "generate1.jpeg");

  return 0;
}
