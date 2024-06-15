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
void printRow(int* boardRow, int row);
void printRowSeparator();
void printBottomBorder();
void printBoard(int** boardToPrint);
pathTree findAllPossibleKnightPaths(chessPos *startingPosition);
chessPosCell *createNewChessPosCell(chessPos pos);
void appendChessPosToList(chessPosList *lst, chessPos pos);
BOOL isWithinBoard(int row, int col);
BOOL findKnightTour(chessPos currentPos, int moveCount, BOOL visited[5][5], chessPosList *path, pathTree *path_tree);
chessPosList *findKnightPathCoveringAllBoard(pathTree *path_tree);
chessPosCell *createNewCell(char pos[2], chessPosCell *next);
void insertCellToEndList(chessPosList *list, char pos[2]);
chessPosList *createSampleList();
chessPosArray*** validKnightMoves(void);
int** InitializeMatrix(int rows, int cols, int value);
void FreeMatrix(int** board, int rows);
void RemoveCellFromList(chessPosList *list, chessPosCell *prevCell, chessPosCell *cellToRemove);

#endif // PROTOTYPES_H
