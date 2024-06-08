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
void display(chessPosList *list);
void removeDuplicates(chessPosList *list);
void manageMemory(void);
pathTree findAllPossibleKnightPaths(chessPos *startingPosition);
chessPosList *findKnightPathCoveringAllBoard(pathTree *pathTree);
chessPosArray ***validKnightMoves(void);

#endif // PROTOTYPES_H
