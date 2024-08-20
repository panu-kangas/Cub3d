# Cub3D

Cub3D is a 3D game engine project inspired by the classic game **Wolfenstein 3D**. We implemented this project as part of the curriculum at Hive Helsinki Coding School to explore the fundamentals of raycasting, graphics rendering, and game development. The game allows players to navigate through a 3D maze, interact with enemies, and find exits, all rendered using a custom-built engine and C.

## Table of Contents
- [Overview](#overview)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Game Mechanics](#game-mechanics)
- [Bonus Features](#bonus-features)
- [Project Structure](#project-structure)
- [Contributing](#contributing)
- [License](#license)

## Overview

Cub3D is a first-person shooter game that demonstrates the power of raycasting to create a 3D experience from a 2D map. We built this engine from the ground up, handling everything from graphics rendering to player input and enemy AI. The project uses the [**MLX42** library](https://github.com/codam-coding-college/MLX42) for graphics and runs on Linux and macOS or WSL2+XServer on Windows.

## Features

- **Raycasting Engine**: Our engine simulates a 3D environment using raycasting techniques.
- **Texture Mapping**: We implemented texture mapping to enhance visual realism.
- **Player Movement**: Smooth player movement with keyboard controls and mouse rotation.
- **Enemy Interaction**: Enemies attack the player, and the player can fight back using a weapon.

## Installation

To install and run Cub3D, follow these steps:

1. **Clone the repository**:
   ```bash
   git clone https://github.com/Lauri-Litovuo/Cub3d
   cd cub3d
2. **Compile the project**:
- **For the standard version**:
   ```bash
   make
- **For the bonus version with additional features**:
   ```bash
   make bonus
3. **Run the game**:
   ```bash
   ./cub3D [map_path]
**Example**:
	```bash
	./cub3D ./maps/levels/level1.cub

## Usage

Once the game is running, use the following controls to navigate and interact:

- **W/A/S/D**: Move forward, left, backward, and right.
- **Left/Right Arrow Keys && Mouse Movement**: Rotate the view.
- **E/F**: Use doors and exits.
- **Spacebar**: Attack (when enemies are present).
- **ESC**: Quit the game.

Explore the maze, avoid or fight enemies, and find the exit to win the game!

## Game Mechanics

- **Raycasting**: We implemented a raycasting algorithm to project a 3D view from a 2D map. Rays are cast from the player’s viewpoint, and the distance to the nearest wall is calculated to determine the height of the walls on the screen.
- **Texture Mapping**: Textures are applied to the walls based on where the rays hit, creating a realistic environment.
- **Player Interaction**: The player can move through the map, rotate their view, and interact with enemies and objects.

## Bonus Features

In addition to the core features, we implemented several advanced features to enhance gameplay:

- **Attacking Enemies**: Enemies now attack the player, and the player can fight back using a weapon.
- **Minimap**: A minimap displays the player's position and nearby environment, providing better orientation.
- **Mouse Rotation**: The player can use the mouse to rotate the view for more intuitive control.
- **Start Screen**: The game starts with a custom-designed start screen.
- **Exits Within Map**: Players must find exits within the map to progress or win.
- **Weapon Animation**: We added animations to the weapon, making combat more dynamic.
- **Killing Enemies**: Players can kill enemies using their weapon, with proper animations and effects.

## Project Structure

Our project is organized as follows:

	```
	cub3d/
	├── srcs/ #**Source code files**
	|	├──mandatory/
	|	└── bonus/
	├── incl/ # Header files
	├── lib/ # Engine and own c lib functions
	├── maps/ # Example map files
	|	└── invalid/
	├── textures/ # Test textures to showcase the directions
	├── tiles/ # Textures used in the game
	|	├── door/
	|	├── exit/
	|	├── wall/
	├── sprites/ # Sprites used in the game
	|	├── enemy/
	|	├── gun/
	|	├── menu/
	|	└── minimap/
	├── map_generators/ # Programs for maze generation
	├── Makefile # Build script
	├── run_invalid_maps.sh # Tester for map parsing
	└── README.md # Project documentation

## Contributing

- [@Lauri-Litovuo](https://github.com/Lauri-Litovuo)
- [@panu-kangas](https://github.com/panu-kangas)

## Acknowledgements
We used ready made sprites to make this game possible. Hence we would like to thank the following creators:
- **Sprites**:


## License

Cub3D is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.
