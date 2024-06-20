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
pathTree findAllPossibleKnightPaths(chessPos* startingPos);
treeNode* createNode(chessPos pos);
void freePathTree(pathTree tree);
void freeTreeNode(treeNode* node);
void addNodeToList(treeNodeList* lst, treeNode* node);
BOOL posInPath(chessPos* path, unsigned int size, chessPos pos);
void buildPathTree(treeNode* curr, chessPosArray*** knightMoves, BOOL visited[BOARD_SIZE][BOARD_SIZE], chessPos* path, unsigned int pathSize);
chessPosList *findKnightPathCoveringAllBoard(pathTree *path_tree);
BOOL addPositionToPath(chessPosList *path, chessPos position);
BOOL findPath(treeNode *node, BOOL visited[BOARD_SIZE][BOARD_SIZE], chessPosList *path);
BOOL allPositionsCovered(BOOL visited[BOARD_SIZE][BOARD_SIZE]);
void removeLastPositionFromPath(chessPosList *path);
void freePath(chessPosList *path);
chessPosArray*** validKnightMoves();
void getFreed(chessPosArray*** validKnightMoves);
int** InitializeMatrix(int rows, int cols, int value);
void FreeMatrix(int** board, int rows);
void RemoveCellFromList(chessPosList *list, chessPosCell *prevCell, chessPosCell *cellToRemove);
BOOL isPositionValid(char* startingPosition);

#endif // PROTOTYPES_H
