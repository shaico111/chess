# Test Suite for Chess Knight Movement Simulation

## Overview

This directory contains the test suite for the Chess Knight Movement Simulation project. The tests are designed to verify the functionality and reliability of different components within the project. Each test file corresponds to a specific module or feature of the application.

## Test Files

- `test_chessGameLogic.c`: Tests the game logic for chess, particularly focusing on the movements and rules associated with the knight piece.
- `test_pathFinding.c`: Verifies the pathfinding algorithms that calculate possible moves for a knight across the chessboard.
- `test_displayFunctions.c`: Checks the display functions to ensure the chessboard and knight's path are correctly visualized.
- `test_prototypes.c`: Ensures that all functions declared in `prototypes.h` are correctly prototyped and match their implementations.

## Running the Tests

To run the tests, ensure that you have the GCC compiler installed and your working directory is the project root. You can compile and run the tests using the provided Makefile. Use the following commands:

```bash
make test  # Compiles and runs all the test cases
```
This command will execute all the tests in the directory and report any failures or errors, helping to ensure that each part of the application functions as expected.

## Dependencies

The tests require the following to be installed:
- GCC compiler
- Standard C library
No external libraries are needed unless explicitly added to the project for enhanced functionality.


### Explanation and Usage

- **Overview**: Describes what the tests are intended for.
- **Test Files**: Lists and explains what each test file does.
- **Running the Tests**: Provides explicit instructions on how to compile and run the tests using the Makefile.
- **Dependencies**: Notes any requirements needed to run the tests.