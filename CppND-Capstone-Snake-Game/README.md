# CPPND: Capstone Snake Game Example

This is a starter repo for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). The code for this repo was inspired by [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl) excellent StackOverflow post and set of responses.

<img src="img/snake_game.gif"/>

The Capstone Project gives you a chance to integrate what you've learned throughout this program. This project will become an important part of your portfolio to share with current and future colleagues and employers.

In this project, you can build your own C++ application or extend this Snake game, following the principles you have learned throughout this Nanodegree Program. This project will demonstrate that you can independently create applications using a wide range of C++ features.

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  >Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source. 
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./snake.

## How to play

When start game, you need to enter your name then press enter
To play game, use the arrow to change direction of snake and eat the food
press SPACE to pause/resume game

## Project Rubric
README (All Rubric Points REQUIRED)
    - A README with instructions is included with the project: Done
    - The README indicates the new features you added to the game: Done
    - The README includes information about each rubric point addressed: Done

Compiling and Testing (All Rubric Points REQUIRED)
    The submission must compile and run without errors on the Udacity project workspace
        * header files are moved to include, image moved to img/
        * CmakeLists.txt is modifed to build with new folder architecture
        * project can be built with cmake and make.
        * project can be run without errors.

1. Loops, Functions, I/O - meet at least 2 criteria
    The project demonstrates an understanding of C++ functions and control structures.\
        - A variety of control structures are added to the project.
        - The project code is clearly organized into functions.
    The project reads data from a file and process the data, or the program writes data to a file.
        * user's name and score are saved in ./build/Log/snakelog.txt
    The project accepts user input and processes the input.
        * project get user name from input and save it to ./build/Log/snakelog.txt
    The project accepts user input and processes the input.
        -The project uses data structures and immutable variables.
        -The project uses arrays or vectors and uses constant variables.

2. Object Oriented Programming - meet at least 3 criteria
    - One or more classes are added to the project with appropriate access specifiers for class members.
        * sysLog class added to save player's infomation into files
    - Class constructors utilize member initialization lists.
        * like in Game and Renderer classes
    - Classes abstract implementation details from their interfaces.
        * functions are name with meaningfull name so we can know what it does via it's name
    - Overloaded functions allow the same function to operate on different parameters.
        One function is overloaded with different signatures for the same function name.
    - Classes follow an appropriate inheritance hierarchy with virtual and override functions.
        Inheritance hierarchies are logical. One member function in an inherited class overrides a virtual base class member function.
    - Templates generalize functions or classes in the project.
        One function or class is declared with a template that allows it to accept a generic parameter.

3. Memory Management - meet at least 3 criteria
    - The project makes use of references in function declarations.
        * Many functions use pointers when declare like UpdateBody, UpdateHead...
    - The project uses destructors appropriately.
        * see sysLog, Renderer
    - The project uses scope / Resource Acquisition Is Initialization (RAII) where appropriate.
        The project follows the Resource Acquisition Is Initialization pattern where appropriate, by allocating objects at compile-time, initializing objects when they are declared, and utilizing scope to ensure their automatic destruction.
    - The project follows the Rule of 5.
        For all classes, if any one of the copy constructor, copy assignment operator, move constructor, move assignment operator, and destructor are defined, then all of these functions are defined.
    - The project uses move semantics to move data instead of copying it, where possible.
        The project relies on the move semantics, instead of copying the object.
    - The project uses smart pointers instead of raw pointers.
        * The project uses at least one smart pointer: unique_ptr, shared_ptr, or weak_ptr: shared_ptr in main.c:9

4. Concurrency - meet at least 2 criteria
    - The project uses multithreading.
        The project uses multiple threads or async tasks in the execution: see game.cpp: 99
    - A promise and future is used in the project.
        A promise and future is used to pass data from a worker thread to a parent thread in the project code.
    - A mutex or lock is used in the project.
        A mutex or lock (e.g. std::lock_guard or `std::unique_lock) is used to protect data that is shared across multiple threads in the project code.
    - A condition variable is used in the project.
        A std::condition_variable is used in the project code to synchronize thread execution.

## Some functions added
1.	Recorded the player's history in the sysLog class.
2.	Added additional obstacles for the snake.
3.	Implemented the pause/resume functionality for the game.

## CC Attribution-ShareAlike 4.0 International


Shield: [![CC BY-SA 4.0][cc-by-sa-shield]][cc-by-sa]

This work is licensed under a
[Creative Commons Attribution-ShareAlike 4.0 International License][cc-by-sa].

[![CC BY-SA 4.0][cc-by-sa-image]][cc-by-sa]

[cc-by-sa]: http://creativecommons.org/licenses/by-sa/4.0/
[cc-by-sa-image]: https://licensebuttons.net/l/by-sa/4.0/88x31.png
[cc-by-sa-shield]: https://img.shields.io/badge/License-CC%20BY--SA%204.0-lightgrey.svg
