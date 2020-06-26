# (Second) Second Life - [The Office] Game

This project is a game based on [The Office][] TV Show made with C++ and [SDL2][SDL] using [CMake][] as the build system.

## Dependencies

**For Debian/Ubuntu**

```sh
sudo apt install git build-essential pkg-config cmake cmake-data libsdl2-dev libsdl2-image-dev
```

## Build

```sh

# Clone this repo
git clone https://github.com/ygunarso/second-second-life.git

# Create a build directory
cd second-second-life
mkdir build
cd build

# Build the project
cmake ..
make

# Run the application
./second-second-life
```

## Resources
 - [LazyFoo][]
 - [Let's Make Games][]
 - [CMake for SDL2 Project][]

[LazyFoo]: http://lazyfoo.net/tutorials/SDL/index.php
[Let's Make Games]: https://www.youtube.com/watch?v=QQzAHcojEKg&list=PLhfAbcv9cehhkG7ZQK0nfIGJC_C-wSLrx
[CMake for SDL2 Project]: https://github.com/aminosbh/basic-cpp-sdl-project
[SDL]: https://www.libsdl.org
[CMake]: https://cmake.org
[The Office]: https://www.nbc.com/the-office
