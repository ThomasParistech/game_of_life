# Game Of Life

Implementation of Conway's Game of Life.

## 1 - Installation

First, clone the repository.
```
git clone https://github.com/ThomasParistech/game_of_life.git
```
Then, go to the directory and compile it.
```
cd game_of_life
mkdir build
cd build
cmake ..
make -j6
```
Please note that CMakeLists.txt is configured in a such way that the executable is generated in the "bin" directory.

## 2 - Running

Go to the build directory and run the app
```
bin/main
```

![](./game_of_life.gif)

