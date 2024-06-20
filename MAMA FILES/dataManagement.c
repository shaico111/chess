/**
 * @file dataManagement.c
 *
 * @brief Manages data structures and memory allocation across the application.
 *
 * Provides functions to add and remove items from data structures like lists,
 * ensuring that memory is efficiently used and properly cleaned up. This includes
 * functions to initialize matrices, free allocated matrices, remove cells from lists,
 * and validate chess board positions.
 *
 * @authors
 * Ben Vaanunu
 * Shai Cohen
 */

#ifndef DATAMANAGEMENT_C
#define DATAMANAGEMENT_C

#include "macros.h"
#include "typedefs.h"
#include "prototypes.h"

/**
 * @brief Initializes a matrix and fills it with a specified value.
 *
 * Allocates memory for a matrix using calloc. Each element in the matrix
 * is set to a given value. If memory allocation fails at any point, the
 * program will terminate with an error message.
 *
 * @param rows The number of rows in the matrix.
 * @param cols The number of columns in the matrix.
 * @param value The value to fill in the matrix.
 * @return A pointer to the allocated matrix.
 */
int** InitializeMatrix(int rows, int cols, int value) {
    int** board = (int**)calloc(rows, sizeof(int*));
    if (board == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    for (int row = 0; row < rows; row++) {
        board[row] = (int*)calloc(cols, sizeof(int));
        if (board[row] == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
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

/**
 * @brief Frees the memory allocated for a matrix.
 *
 * Iterates through each row of the matrix and frees the memory,
 * followed by freeing the memory allocated for the matrix itself.
 *
 * @param board A pointer to the matrix to be freed.
 * @param rows The number of rows in the matrix.
 */
void FreeMatrix(int** board, int rows) {
    for (int row = 0; row < rows; row++) {
        free(board[row]);
    }
    free(board);
}

/**
 * @brief Removes a specified cell from a linked list.
 *
 * If the cell to remove is the head of the list, it updates the head.
 * If it's the tail, updates the tail. Ensures that all pointers are correctly
 * reassigned, and the memory for the removed cell is freed.
 *
 * @param list The list from which to remove the cell.
 * @param prevCell The cell immediately preceding the one to remove.
 * @param cellToRemove The cell to be removed.
 */
void RemoveCellFromList(chessPosList *list, chessPosCell *prevCell, chessPosCell *cellToRemove) {
    if (cellToRemove == NULL) {
        return; // Nothing to remove
    }

    if (prevCell == NULL) {
        list->head = cellToRemove->next;
        if (list->head == NULL) {
            list->tail = NULL; // List is empty after removal
        }
    } else {
        prevCell->next = cellToRemove->next;
        if (cellToRemove->next == NULL) {
            list->tail = prevCell; // Updating tail if necessary
        }
    }

    free(cellToRemove);
}

/**
 * @brief Validates whether a position is within the chess board limits.
 *
 * Checks if the provided position is within the valid range of the chess board,
 * based on predefined board size.
 *
 * @param startingPosition The position to validate, represented as a 2-character array.
 * @return TRUE if the position is valid, FALSE otherwise.
 */
BOOL isPositionValid(char* startingPosition) {
    return startingPosition[0] >= 'A' && startingPosition[0] < 'A' + BOARD_SIZE &&
           startingPosition[1] >= '1' && startingPosition[1] < '1' + BOARD_SIZE;
}

#endif
