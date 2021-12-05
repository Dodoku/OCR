# Dodoku - Documentation
**In order to correctly use the functionalities of this software you can refer to this documentation.**

To build all the modules, you can use `make` which will create all the executables in `build/`

*For the moment the software is only used in the form of modules*
## Image Processing
First you have to build the executable of the module with `make module/imageProcess`
### Rotation
To apply a rotation to an image you can use the command `./build/imageProcess rotate [path-src] [path-dest] [degree]`
### Filters
To apply a filter to an image you can use the command `./build/imageProcess [filter] [path-src] [path-dest]`
Filter :
* `greyscale` : transforms the image into black and white 
* `blur` + `n` : blur the image n times
* `otsu` : highlights the forumes in the image with binarization

To apply all filters you can use filter `all`

To apply the filter on all images you can use `./build/imageProcess all - -`

## Image Splitting
First you have to build the executable of the module with `make module/imageSpliter`

to split a picture, use `./build/imageSpliter [path]`
## Neural Network
First you have to build the executable of the module with `make module/neuralNetwork`
### XOR Network
You have two choices, 
* Either you can use `./build/neuralNetwork` without specifying any arguments so that the network learns the XOR by itself. He will then give you the values he found after his workout and you will have the option to save the workout values before leaving.
* Otherwise, if you already have the file with the trained neural network you can load it with `./build/neuralNetwork [path]`. It will load the data into the network and then it will give you the values that get.
### Number Network
*Not available yet*
## Solving Sudoku
>This module allows to solve a sudoku from a file respecting this format
>```
>... ..4 58.
>4.3 ... ...
>
>21. .67 ..4
>.7. ... 2..
>63. .49 ..1
>
>3.6 ... ...
>... 158 ..6
>... ..6 95.
>```
First you have to build the executable of the module with `make module/solver`

Then you just have to use this command `./build/solver [path]` by specifying the path of the file where the grid to solve is located.

The resolved grid will be in the same place as the original one with the extension `.out`
## Output Image Generation
>This module allows to generate image from a file respecting this format
>```
>127 634 589
>589 721 643
>463 985 127
>
>218 567 394
>974 813 265
>635 249 871
>
>356 492 718
>792 158 436
>841 376 952
>```
First you have to build the executable of the module with `make module/imageGenerator`

Then you just have to use this command `./build/imageGenerator [path]` by specifying the path of the file where the grid to generate is located.

The generated image will be in the same place as the original sudoku with the extension `.jpeg`.

