/**
 * File: pathFinding.c
 * --------------------
 * Algorithms to find paths on the chessboard that a knight can follow.
 * These include finding all possible paths and optimal paths covering all squares.
 */

#include "../include/typedefs.h"
#include "../include/prototypes.h"
#include "../include/macros.h"

chessPosList *findKnightPathCoveringAllBoard(pathTree *path_tree) {
    // Check if the path_tree is NULL
    if (path_tree == NULL || path_tree->root == NULL) {
        return NULL;
    }

    // Initialize the visited array and the list to store the path
    BOOL visited[BOARD_SIZE][BOARD_SIZE] = {FALSE};
    chessPosList *path = (chessPosList*)malloc(sizeof(chessPosList));
    if (path == NULL) {
        printf("Memory allocation error\n");
        exit(1);
    }
    path->head = path->tail = NULL;

    // Start DFS from the root of the path tree
    if (findPath(path_tree->root, visited, path)) {
        return path;
    } else {
        freePath(path); // Free the path if no complete path is found
        return NULL;
    }
}

// Helper function to add position to the path
BOOL addPositionToPath(chessPosList *path, chessPos position) {
    chessPosCell *newCell = (chessPosCell*)malloc(sizeof(chessPosCell));
    if (newCell == NULL) {
        printf("Memory allocation error\n");
        return FALSE;
    }
    newCell->position[0] = position[0];
    newCell->position[1] = position[1];
    newCell->next = NULL;

    if (path->head == NULL) {
        path->head = path->tail = newCell;
    } else {
        path->tail->next = newCell;
        path->tail = newCell;
    }
    return TRUE;
}

// Recursive function to find a path that covers all board using DFS
BOOL findPath(treeNode *node, BOOL visited[BOARD_SIZE][BOARD_SIZE], chessPosList *path) {
    int row = node->position[0] - 'A';
    int col = node->position[1] - '1';

    // Mark this node as visited
    if (visited[row][col]) {
        return FALSE; // Already visited this position
    }
    visited[row][col] = TRUE;
    addPositionToPath(path, node->position);

    // Check if all positions are visited
    if (allPositionsCovered(visited)) {
        return TRUE;
    }

    // Explore each child
    treeNodeListCell *child = node->next_possible_positions.head;
    while (child != NULL) {
        if (findPath(child->node, visited, path)) {
            return TRUE; // Path found through this child
        }
        child = child->next;
    }

    // Backtrack
    removeLastPositionFromPath(path);
    visited[row][col] = FALSE;
    return FALSE;
}

// Checks if all positions on the board are covered
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

// Removes the last position from the path
void removeLastPositionFromPath(chessPosList *path) {
    if (path->head == NULL) return; // Empty path

    chessPosCell *current = path->head;
    chessPosCell *prev = NULL;

    while (current->next != NULL) {
        prev = current;
        current = current->next;
    }

    if (prev == NULL) {
        // Only one element
        free(path->head);
        path->head = path->tail = NULL;
    } else {
        free(current);
        prev->next = NULL;
        path->tail = prev;
    }
}

// Function to free the path list
void freePath(chessPosList *path) {
    chessPosCell *current = path->head;
    chessPosCell *next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    free(path);
}
