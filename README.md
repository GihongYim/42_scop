Subject: scop
	for ubuntu in 42Seoul cluster

Minimal C++98 OpenGL 3.3 Core project using GLFW and GLAD.

## Dependencies

```sh
sudo apt update
sudo apt install build-essential pkg-config libglfw3-dev libgl1-mesa-dev
```

## Build

```sh
make
./scop
```

If you do not have sudo access, build GLFW locally inside the project:

```sh
make glfw
make
./scop
```

## CMake Build

```sh
cmake -S . -B build
cmake --build build
./build/scop
```
