# BlockGL

**Minecraft Clone Voxel Engine written using C++23 and OpenGL**

### Why this project?
I chose to make a minecraft clone project because I wanted to learn more about computer graphics and engine level development. When I was a kid I always used to play minecraft it was my favorite game, the amount of Creativity and the Building was my favorite part. Thats how I came to the conclusion to make a mini minecraft clone since I saw a few Videos how other people recreated it I got onto vscode and started coding this minecraft clone.

## Gameplay

- Building Trees and Ambience
![Building Trees and Ambience](./screenshots/gameplay1.png)
- Building a House
![Building a House](./screenshots/gameplay2.png)

## How to Build this Project
- Build using CMake

- Clone the repo into a folder
```shell
    git clone --recursive https://github.com/omedcodes/BlockGL.git
```

- Build the project (Windows Mingw64) *I recommend built type to be Release and using mingw64 shell AS ADMINISTRATOR*
```shell
    cd BlockGL
    mkdir build
    cd build
    cmake .. -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release -DCMAKE_POLICY_VERSION_MINIMUM=3.5
```
- Once setup compile *it can compile little slower on low end devices again make sure it runs as ADMINISTRATOR*
```shell
    mingw32-make -j2
```

- Run
```shell
    ./BlockGL.exe
```