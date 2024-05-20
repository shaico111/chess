# Chess Knight Movement Simulation

## Project Overview

This project simulates the movement of a knight on a chessboard. It is developed in C and focuses on algorithmic challenges like calculating all possible moves for a knight and determining paths that cover all squares on a board.

## Team

**Authors:**
- Shai Cohen
- Ben Vaanunu

## Structure and Compilation

### Source Files
- **main.c**: Initializes the game and handles user interactions.
- **chessGameLogic.c**: Manages chess rules and knight movements.
- **pathFinding.c**: Implements algorithms for generating knight's paths.
- **displayFunctions.c**: Handles the graphical representation of board states.
- **memoryManagement.c**: Ensures efficient memory management throughout the application.

### Header Files
- **main.h**: Includes main function declaration.
- **prototypes.h**: Contains prototypes for all functions used in the project.
- **typedefs.h**: Defines all custom types and structures used in the project.

### Compilation
Compile the project using the following command:
```bash
gcc -o chessSim main.c chessGameLogic.c pathFinding.c displayFunctions.c memoryManagement.c -I.
./chessSim

```

## Features

- **Interactive Input:** The user can input a starting position for the knight.
- **Path Simulation:** The application calculates and displays possible paths or a specific path that covers all squares, based on user choice.

## Acknowledgments

We thank our peers and instructors for their guidance and support throughout the semester.
