/**
 * @file KnightTourSolver.c
 *
 * @brief Implements a solution to the Knight's Tour problem using depth-first search (DFS).
 *
 * This file contains functions essential for calculating a complete knight's tour on a chess board.
 * It leverages depth-first search (DFS) to navigate through possible routes starting from a designated
 * position. If a tour that covers all board squares exactly once is found, it produces a linked list
 * detailing the sequence of moves. Conversely, if no feasible tour is available, it returns NULL, signaling
 * the absence of a valid path that can traverse all board slots.
 */


#include "../include/typedefs.h"
#include "../include/prototypes.h"

/**
 * Attempts to find a knight's tour that covers all positions on the board.
 * @param path_tree A tree structure representing all possible knight moves from the starting position.
 * @return A linked list of all positions in the order visited by the knight to cover the board, or NULL if no tour is possible.
 */
chessPosList *findKnightPathCoveringAllBoard(pathTree *path_tree) {
    if (path_tree == NULL || path_tree->root == NULL) {
        return NULL; // Validate input, return NULL if the input tree is invalid.
    }

    BOOL visited[BOARD_SIZE][BOARD_SIZE] = {FALSE}; // Array to track visited positions.
    chessPosList *path = (chessPosList*)malloc(sizeof(chessPosList));
    if (path == NULL) {
        printf("Memory allocation error\n");
        exit(1); // Handle memory allocation failure.
    }
    path->head = path->tail = NULL;

    // Use DFS to attempt to find a valid path.
    if (findPath(path_tree->root, visited, path)) {
        return path;
    } else {
        freePath(path); // Clean up and return NULL if no valid path is found.
        return NULL;
    }
}

/**
 * Adds a new position to the knight's path.
 * @param path The current path list.
 * @param position The new position to add.
 * @return TRUE if the position is added successfully, FALSE otherwise.
 */
BOOL addPositionToPath(chessPosList *path, chessPos position) {
    chessPosCell *newCell = (chessPosCell*)malloc(sizeof(chessPosCell));
    if (newCell == NULL) {
        printf("Memory allocation error\n");
        return FALSE; // Handle memory allocation failure.
    }
    newCell->position[0] = position[0];
    newCell->position[1] = position[1];
    newCell->next = NULL;

    if (path->head == NULL) {
        path->head = path->tail = newCell; // Initialize the path if it's empty.
    } else {
        path->tail->next = newCell;
        path->tail = newCell; // Append to the end of the path.
    }
    return TRUE;
}

/**
 * Recursive helper function to explore all possible moves using DFS.
 * @param node The current node in the route tree.
 * @param visited Array tracking visited positions.
 * @param path Current path of the tour.
 * @return TRUE if a complete path is found, FALSE otherwise.
 */
BOOL findPath(treeNode *node, BOOL visited[BOARD_SIZE][BOARD_SIZE], chessPosList *path) {
    int row = node->position[0] - 'A';
    int col = node->position[1] - '1';

    if (visited[row][col]) {
        return FALSE; // Check if the current position is already visited.
    }
    visited[row][col] = TRUE;
    addPositionToPath(path, node->position);

    if (allPositionsCovered(visited)) {
        return TRUE; // Check if all positions are covered.
    }

    treeNodeListCell *child = node->next_possible_positions.head;
    while (child != NULL) {
        if (findPath(child->node, visited, path)) {
            return TRUE; // Recurse to the next move.
        }
        child = child->next;
    }

    removeLastPositionFromPath(path); // Backtrack if no path is found.
    visited[row][col] = FALSE;
    return FALSE;
}

/**
 * Checks if all positions on the board have been visited.
 * @param visited Array tracking visited positions.
 * @return TRUE if all positions are visited, FALSE otherwise.
 */
BOOL allPositionsCovered(BOOL visited[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (!visited[i][j]) {
                return FALSE;
            }
        }
    }
    return TRUE;
}

/**
 * Removes the last position from the current path.
 * @param path The current path list.
 */
void removeLastPositionFromPath(chessPosList *path) {
    if (path->head == NULL) return; // Check if the path is empty.

    chessPosCell *current = path->head, *prev = NULL;
    while (current->next != NULL) {
        prev = current;
        current = current->next;
    }

    if (prev == NULL) {
        free(path->head); // If only one element exists.
        path->head = path->tail = NULL;
    } else {
        free(current);
        prev->next = NULL;
        path->tail = prev; // Remove the last element and update the tail.
    }
}

/**
 * Frees all memory allocated to the path list.
 * @param path The path list to free.
 */
void freePath(chessPosList *path) {
    chessPosCell *current = path->head, *next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    free(path);
}
