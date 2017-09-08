# tinyc2-tests
Multiple test/example C++ files for [tinyc2](https://github.com/randygaul/tinyheaders).

## Requirements
* [SFML 2.4.x](https://github.com/sfml/sfml)
* [premake5](https://premake.github.io) (optional)

## How to use
`tinyc2-tests` is using [premake5](https://premake.github.io) to assist the generation of cross platform make/project files. To compile all the tests using `premake5` run the following command:
```sh
premake5 <action> && cd build && make
```
Where `<action>` specifies your build tools (e.g. 'gmake' for Gnu make or 'vs2013' for Visual Studio 2013). For further help on using premake visit the [official documentation](https://github.com/premake/premake-core/wiki/Using-Premake).  
After the build has finished, you can find all the binaries inside `build/bin/{Debug/Release}/`.

## Manual installation
As `tinyc2.h` is included with `tinyc2-tests` you only need to install and link against `SFML 2.4.x`. For Linux a simple g++ command should suffice:
```sh
g++ circle/CircleToCircle.cpp -I. -lsfml-graphics -lsfml-window -lsfml-system
```

## Controls
Used `wasd` to move the shape across the screen (not working for `PolygonToX` yet). For `RayToX` tests the ray's direction can be manipulated by moving the mouse.

## License
`tinyc2-tests` uses the same license as `tinyheaders`, the [zlib license](https://www.zlib.net/zlib_license.html).
