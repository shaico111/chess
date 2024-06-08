/* File: prototypes.h
 * -------------------
 * This header file includes declarations of all the functions used in the chessboard
 * project. It provides a central place to see all operations related to chess
 * game logic and movement.
 */

#ifndef PROTOTYPES_H
#define PROTOTYPES_H

#include "typedefs.h"  // Include type definitions for function prototypes.

// Function prototypes
chessPosArray ***validKnightMoves(void);
void display(chessPosList *list);

// Function prototypes for path tree calculations.
pathTree findAllPossibleKnightPaths(chessPos *startingPosition);
chessPosList *findKnightPathCoveringAllBoard(pathTree *pathTree);

#endif // PROTOTYPES_H