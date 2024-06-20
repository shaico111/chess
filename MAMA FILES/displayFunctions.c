/**
 * @file displayFunctions.c
 *
 * @brief Provides functions to manage the display of the chessboard and the knight's path.
 *
 * This module includes functions for initializing the display matrix, marking the knight's
 * path on the board, and printing the entire board to the console. It handles all aspects
 * of visual representation of the game state.
 *
 * @authors
 * Ben Vaanunu
 * Shai Cohen
 */

#include "macros.h"
#include "typedefs.h"
#include "prototypes.h"

/**
 * @brief Displays the chessboard with the knight's path marked.
 *
 * Initializes a matrix for the chessboard, processes the list of positions to mark
 * them on the board, and then prints the board to the console.
 *
 * @param list A pointer to the chessPosList containing the knight's path.
 */
void display(chessPosList *list) {
    int** boardToPrint = InitializeMatrix(BOARD_SIZE, BOARD_SIZE, 0);
    HandleChessPosList(list, boardToPrint);
    printBoard(boardToPrint);
}

/**
 * @brief Processes a list of chess positions and marks them on the chessboard.
 *
 * Iterates through the list of chess positions, verifying each for correctness
 * and uniqueness. Marks each valid position on the board and removes any invalid
 * or duplicate positions from the list.
 *
 * @param list A pointer to the chessPosList to be processed.
 * @param board A double pointer to an int, representing the chessboard matrix.
 */
void HandleChessPosList(chessPosList *list, int** board) {
    chessPosCell *prevCell = NULL, *currCell = list->head;
    int row, col, cellsCounter = 0;

    // Initialize the board with zeros
    InitializeMatrix(BOARD_SIZE, BOARD_SIZE, 0);

    // Process each cell in the list
    while(currCell != NULL) {
        row = CELL_TO_ROW(currCell->position);
        col = CELL_TO_COL(currCell->position);

        if (IS_CHESS_POS_CELL_CORRECT(currCell->position) && (board[row][col] == 0)) {
            board[row][col] = ++cellsCounter; // Mark its sequence position on the board
            prevCell = currCell;
            currCell = currCell->next;
        } else {
            chessPosCell *cellToRemove = currCell;
            currCell = currCell->next;
            RemoveCellFromList(list, prevCell, cellToRemove);
        }
    }
}

/**
 * @brief Prints the top row of column numbers for the chessboard.
 */
void printColumnNumbers() {
    printf("   ");
    for (int col = 1; col <= BOARD_SIZE; col++) {
        printf(" %d ", col);
    }
    printf("\n");
}

/**
 * @brief Prints a single row of the chessboard.
 *
 * @param boardRow An array representing a single row of the chessboard.
 * @param row The row number, used to print the row label.
 */
void printRow(int* boardRow, int row) {
    printf("%c|", 'A' + row);

    for (int col = 0; col < BOARD_SIZE; col++) {
        if (boardRow[col] != 0) {
            printf("%2d", boardRow[col]);
        } else {
            printf("  ");
        }
        printf("|");
    }
    printf("\n");
}

/**
 * @brief Prints the entire chessboard with markings.
 *
 * Calls helper functions to print column numbers and each row.
 *
 * @param boardToPrint A double pointer to an int, representing the chessboard matrix.
 */
void printBoard(int** boardToPrint) {
    printColumnNumbers();

    for (int row = 0; row < BOARD_SIZE; row++) {
        printRow(boardToPrint[row], row);
    }
}
