*This project has been created as part of the 42 curriculum by ygh04.*

# scop

## Description

`scop` is a C++98 OpenGL project that parses Wavefront `.obj` files and renders them in perspective. The object is normalized around its own center, displayed with subtle grayscale face colors, and can be translated or rotated around its main axes. Pressing `T` smoothly blends between the colored view and a generated cheerful texture.

The default model is the provided 42 logo at `assets/42.obj`. Additional provided objects, including `assets/teapot.obj` and `assets/teapot2.obj`, can be passed as runtime arguments.

## Instructions

Ubuntu dependency command:

```sh
sudo apt update && sudo apt install -y build-essential cmake pkg-config libglfw3-dev libgl1-mesa-dev
```

Ubuntu build and run:

```sh
make
./scop assets/42.obj
```

Ubuntu CMake run script:

```sh
./run.sh assets/teapot2.obj
```

Windows build and run from PowerShell:

```powershell
.\run.ps1
```

If double-clicking `run.ps1` opens Notepad, use `run.bat` instead or run the command above from PowerShell.

Windows double-click run:

```bat
run.bat
```

Run another model on Windows:

```powershell
.\run.ps1 -Model assets\teapot2.obj
```

Clean and rebuild on Windows:

```powershell
.\run.ps1 -Clean
```

## Controls

- `Esc`: quit
- `W` / `S`: move on Z
- `A` / `D`: move on X
- `Q` / `E`: move on Y
- `I` / `K`: rotate around X
- `J` / `L`: rotate around Y
- `U` / `O`: rotate around Z
- `T`: toggle texture with smooth transition
- `R`: toggle automatic central-axis rotation

## Technical Choices

- GLFW is used only for window and event management.
- OBJ parsing, shader loading, matrix math, model normalization, UV projection, and texture generation are implemented in the project.
- Faces with more than three vertices are triangulated with a fan strategy for the mandatory part.
- When an OBJ does not provide texture coordinates, the renderer generates projected UVs from the normalized position and face normal.

## Resources

- 42 `scop` subject PDF: `en.subject.pdf`
- Provided project resources: `resources.tgz`
- OpenGL reference: https://registry.khronos.org/OpenGL-Refpages/
- GLFW documentation: https://www.glfw.org/docs/latest/
- Wavefront OBJ format reference: https://www.loc.gov/preservation/digital/formats/fdd/fdd000507.shtml

AI was used to review the subject requirements, compare them against the current implementation, and help draft implementation steps. All generated code and design choices were reviewed and integrated manually in this repository.
