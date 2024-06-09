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

void InitializeMatrix(int** board, int rows, int cols, int value) {
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            board[col][row] = value;
        }
    }
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

#endif