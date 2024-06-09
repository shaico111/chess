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
void HandleChessPosList(chessPosList *list, int** board);
void printColumnNumbers();
void printTopBorder();
void printRow(char boardRow[BOARD_SIZE], int row);
void printRowSeparator();
void printBottomBorder();
void printBoard(char boardToPrint[BOARD_SIZE][BOARD_SIZE]);
pathTree findAllPossibleKnightPaths(chessPos *startingPosition);
chessPosList *findKnightPathCoveringAllBoard(pathTree *pathTree);
chessPosArray ***validKnightMoves(void);
void InitializeMatrix(int** board, int rows, int cols, int value);
void RemoveCellFromList(chessPosList *list, chessPosCell *prevCell, chessPosCell *cellToRemove);

#endif // PROTOTYPES_H
