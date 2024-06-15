/**
 * File: pathFinding.c
 * --------------------
 * Algorithms to find paths on the chessboard that a knight can follow.
 * These include finding all possible paths and optimal paths covering all squares.
 */

#include "../include/macros.h"
#include "../include/typedefs.h"
#include "../include/prototypes.h"

pathTree findAllPossibleKnightPaths(chessPos *startingPosition) {
    // \TODO: Section 3 - Build a tree of all paths starting from the given position
    pathTree tree;
    return tree;  // Placeholder return
}

// Utility function to create a new chess position cell
chessPosCell *createNewChessPosCell(chessPos pos) {
    chessPosCell *newCell = (chessPosCell *)malloc(sizeof(chessPosCell));
    if (!newCell) {
        // Handle memory allocation failure
        exit(1);
    }
    memcpy(newCell->position, pos, sizeof(chessPos));
    newCell->next = NULL;
    return newCell;
}

// Utility function to append a position to the chess position list
void appendChessPosToList(chessPosList *lst, chessPos pos) {
    chessPosCell *newCell = createNewChessPosCell(pos);
    if (!lst->head) {
        lst->head = lst->tail = newCell;
    } else {
        lst->tail->next = newCell;
        lst->tail = newCell;
    }
}

// Function to check if a position is within the board boundaries
BOOL isWithinBoard(int row, int col) {
    return (row >= 0 && row < 5 && col >= 0 && col < 5);
}

// Recursive utility function to find a knight's tour
BOOL findKnightTour(chessPos currentPos, int moveCount, BOOL visited[5][5], chessPosList *path, pathTree *path_tree) {
    static int rowMoves[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
    static int colMoves[8] = {1, 2, 2, 1, -1, -2, -2, -1};

    int row = currentPos[0] - 'A';
    int col = currentPos[1] - '1';

    if (moveCount == 25) {
        appendChessPosToList(path, currentPos);
        return TRUE;
    }

    visited[row][col] = TRUE;
    appendChessPosToList(path, currentPos);

    for (int i = 0; i < 8; i++) {
        int nextRow = row + rowMoves[i];
        int nextCol = col + colMoves[i];
        if (isWithinBoard(nextRow, nextCol) && !visited[nextRow][nextCol]) {
            chessPos nextPos = {nextRow + 'A', nextCol + '1'};
            if (findKnightTour(nextPos, moveCount + 1, visited, path, path_tree)) {
                return TRUE;
            }
        }
    }

    visited[row][col] = FALSE;
    chessPosCell *temp = path->head;
    path->head = path->head->next;
    free(temp);
    return FALSE;
}

chessPosList *findKnightPathCoveringAllBoard(pathTree *path_tree) {
    BOOL visited[5][5] = {FALSE};
    chessPosList *path = (chessPosList *)malloc(sizeof(chessPosList));
    if (!path) {
        // Handle memory allocation failure
        exit(1);
    }
    path->head = path->tail = NULL;

    if (findKnightTour(path_tree->root->position, 1, visited, path, path_tree)) {
        return path;
    } else {
        free(path);
        return NULL;
    }
}