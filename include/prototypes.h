/* File: prototypes.h
 * -------------------
 * This header file includes declarations of all the functions used in the chessboard
 * project. It provides a central place to see all operations related to chess
 * game logic and movement.
 */

#ifndef PROTOTYPES_H
#define PROTOTYPES_H

#include "typedefs.h"  // Include type definitions for function prototypes.

#include "macros.h"  // Include type macros for function prototypes.

// Function prototypes
void display(chessPosList *list);
void HandleChessPosList(chessPosList *list, int** board);
void printColumnNumbers();
void printTopBorder();
void printRow(int* boardRow, int row);
void printRowSeparator();
void printBottomBorder();
void printBoard(int** boardToPrint);
void logPosition(const char* prefix, chessPos position);
BOOL isPositionValid(chessPos position);
treeNodeList* generateValidMoves(chessPos position, int depth, BOOL visited[BOARD_SIZE][BOARD_SIZE]);
void printPath(chessPosList* path);
static BOOL allPositionsCovered(BOOL visited[BOARD_SIZE][BOARD_SIZE]);
static BOOL findPath(treeNode *node, BOOL visited[BOARD_SIZE][BOARD_SIZE], chessPosList *path, chessPosArray ***moves);
chessPosList *findKnightPathCoveringAllBoard(pathTree *path_tree);
BOOL addPositionToPath(chessPosList* path, chessPos position);
void freePath(chessPosList* path);
void removeLastPositionFromPath(chessPosList* path);
pathTree* initializePathTreeWithRoot(chessPos initialPosition);
chessPosArray*** validKnightMoves();
void getFreed(chessPosArray*** validKnightMoves);
int** InitializeMatrix(int rows, int cols, int value);
void FreeMatrix(int** board, int rows);
void RemoveCellFromList(chessPosList *list, chessPosCell *prevCell, chessPosCell *cellToRemove);

#endif // PROTOTYPES_H
