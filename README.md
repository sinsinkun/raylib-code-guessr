# Raylib project

Project about ???
Maybe immediate mode GUI

## Installation (with MSYS2)
- Go through setup process to get mingw compiler working with VSCode
- Search for raylib package in mingw repository `pacman -Ss raylib`
- Copy package name that matches g++ version (default is ucrt64)
- Install package with `pacman -S {...}`
- (FYI: `-lraylib` flag was added to tasks.json manually)

## Release
- Release build: `g++ -O2 **.cpp -o release/main.exe -std=c++17 -static-libstdc++ -static-libgcc -Wl,-Bstatic -lpthread -Wl,-Bdynamic -lraylib -mwindows`
- Needs to bundle libraylib.dll and libwinpthread-1.dll