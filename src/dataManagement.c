/**
 * File: dataManagement.c
 * -----------------------
 * Manages data structures and memory allocation across the application.
 * Provides functions to add and remove items from data structures like lists,
 * ensuring that memory is efficiently used and properly cleaned up.
 */

#ifndef DATAMANAGEMENT_C
#define DATAMANAGEMENT_C

#include "../include/macros.h"
#include "../include/typedefs.h"
#include "../include/prototypes.h"

// Function to initialize the matrix using calloc and fill it with a specified value
int** InitializeMatrix(int rows, int cols, int value) {
    // Allocate memory for the rows
    int** board = (int**)calloc(rows, sizeof(int*));
    if (board == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    // Allocate memory for the columns in each row and fill with the specified value
    for (int row = 0; row < rows; row++) {
        board[row] = (int*)calloc(cols, sizeof(int));
        if (board[row] == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            // Free previously allocated memory in case of failure
            for (int i = 0; i < row; i++) {
                free(board[i]);
            }
            free(board);
            exit(1);
        }
        for (int col = 0; col < cols; col++) {
            board[row][col] = value;
        }
    }

    return board;
}

// Function to free the allocated matrix
void FreeMatrix(int** board, int rows) {
    for (int row = 0; row < rows; row++) {
        free(board[row]);
    }
    free(board);
}

void RemoveCellFromList(chessPosList *list, chessPosCell *prevCell, chessPosCell *cellToRemove) {
    if (cellToRemove == NULL) {
        return; // Nothing to remove
    }

    if (prevCell == NULL) {
        // Removing the head of the list
        list->head = cellToRemove->next;
        if (list->head == NULL) {
            list->tail = NULL; // If the list becomes empty
        }
    } else {
        prevCell->next = cellToRemove->next;
        if (cellToRemove->next == NULL) {
            list->tail = prevCell; // Update the tail if the last cell is removed
        }
    }

    free(cellToRemove);
}

// Validating position within chess board limits
BOOL isPositionValid(char* startingPosition)
{
    return startingPosition[0] >= 'A' && startingPosition[0] < 'A' + BOARD_SIZE &&
            startingPosition[1] >= '1' && startingPosition[1] < '1' + BOARD_SIZE;
}

#endif