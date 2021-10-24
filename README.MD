# Dodoku - Documentation  
**In order to correctly use the functionalities of this software you can refer to this documentation.**

To build all the modules, you can use `make` which will create all the executables in `build/`

*For the moment the software is only used in the form of modules*
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
