/**
 * @file prototypes.h
 *
 * @brief Declares all functions used within the chessboard project.
 *
 * Provides a centralized declaration of functions, making it easier to understand the
 * operations related to chess game logic and movement, especially focusing on knight's
 * movements and path finding strategies.
 *
 * @authors
 * Ben Vaanunu
 * Shai Cohen
 */
#ifndef PROTOTYPES_H
#define PROTOTYPES_H

#include "typedefs.h"  // Include type definitions for function prototypes.
#include "macros.h"    // Include macro definitions for function prototypes.

// Function prototypes for all operations
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
void buildPathTree(treeNode* curr, chessPosArray*** knightMoves, BOOL visited[BOARD_SIZE][BOARD_SIZE], chessPos* path, unsigned int pathSize);
chessPosArray*** validKnightMoves();
void getFreed(chessPosArray*** validKnightMoves);
int** InitializeMatrix(int rows, int cols, int value);
void FreeMatrix(int** board, int rows);
void RemoveCellFromList(chessPosList *list, chessPosCell *prevCell, chessPosCell *cellToRemove);
BOOL isPositionValid(char* startingPosition);
chessPosList *findKnightPathCoveringAllBoard(pathTree *path_tree);
BOOL addPositionToPath(chessPosList *path, chessPos position);
BOOL findPath(treeNode *node, BOOL visited[BOARD_SIZE][BOARD_SIZE], chessPosList *path);
BOOL allPositionsCovered(BOOL visited[BOARD_SIZE][BOARD_SIZE]);
void removeLastPositionFromPath(chessPosList *path);
void freePath(chessPosList *path);

#endif // PROTOTYPES_H
