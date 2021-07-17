# Practice project: Cub3D
The goal of this project is to write simple game engine with Ray casting algorithm. There is a 2D map in map_simple.cub file, that turns into pseudo 3D game.
#### Map
0 = free space, 1 = wall, 2 = sprite, N/S/W/E - player and his starting orientation.

R - resolution, F - floor color (RGB format), C - ceil color (RGB format), SO/WE/EA/NO - paths to  wall textures (depending on the direction), S - path to sprite image.

#### Control
WASD + arrows for navigating, Esc for exit

#### Compile on Linux:
0) sudo apt-get update && sudo apt-get install xorg libxext-dev zlib1g-dev
1) make
2) ./cub3D map_simple.cub

![](https://i.imgur.com/CDrem7U.jpg)
![](https://i.imgur.com/aX36iZ8.jpg)
![](https://i.imgur.com/cxngDep.jpg)
![](https://i.imgur.com/SsKE6Yi.jpg)
![](https://i.imgur.com/7IuTkhz.jpg)
![](https://i.imgur.com/FXJlJgb.jpg)
