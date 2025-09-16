# 🕹️ cub3D / Wolfenstein-3D

A raycasting-based 3D engine inspired by Wolfenstein 3D, written in C using MiniLibX. The goal is to create a navigable world for practicing ray casting fundamentals. There are no characters, collectibles, or advanced gameplay elements—just pure ray casting and exploration.

---

## Demo

![Game Demo](./gif/Wolfenstein-3d.gif)

---

## Features

- 3D raycasting engine (Wolfenstein-style)
- Multiple themed levels (ice, sand, pacman, mario, etc.)
- Collectibles, enemies, and exit doors
- Minimap and UI overlays
- Custom asset loading and map parsing
- Keyboard controls for movement and rotation

---

## Controls

- **W(up)A(right)S(down)D(right)**: Move
- **Arrow keys**: Rotate view
- **ESC**: Quit

---

## Customization

You can easily customize your game experience:

- **Colors**: Edit floor and ceiling colors directly in the `.cub` config file.
- **Map Editing**: Modify map layouts and elements by editing the map files in the `maps/` directory. Make sure your map meets the requirements: it must have exactly one player starting position (facing N, S, W, or E), and the map should be fully surrounded by walls.
- **Textures**: Change walls textures by replacing or adding files in the `ass/` folder and updating the paths in the config file. Textures must be ".xpm" files.

---

## Build & Run

```sh
make
./cub3D maps/VALID_SIMPLE.cub
```

---

## Project Structure

- `src/` — Main source files
- `libft/` — Custom C library
- `ass/` — Game assets (sprites, textures)
- `maps/` — Example map files
- `inc/` — Header files

---

## Credits

Developed by [yel-bouk](https://github.com/yahiaelboukili) and [mmalie](https://github.com/mmalie) @42
