/**
 * File: displayFunctions.c
 * -------------------------
 * Functions to manage the display of the chessboard and knight's path.
 * This module handles the visual representation of the game state.
 */

#include "../include/macros.h"
#include "../include/typedefs.h"
#include "../include/prototypes.h"

void display(chessPosList *list) {
    int** boardToPrint = InitializeMatrix(BOARD_SIZE, BOARD_SIZE, 0);
    HandleChessPosList(list, boardToPrint);
    printBoard(boardToPrint);
}


// Reads and verifies the list.
// If a cell is unique and correct, marks it in the board properly.
// Otherwise, removes it.
void HandleChessPosList(chessPosList *list, int** board) {
    chessPosCell *prevCell = NULL, *currCell = list->head;
    int row,col, cellsCounter=0;

    // Initialize the board with zeros
    InitializeMatrix(BOARD_SIZE, BOARD_SIZE, 0);

    // While there are items in the list
    while(currCell != NULL) {
        // Calculate the row and col for the cell;
        row = CELL_TO_ROW(currCell->position);
        col = CELL_TO_COL(currCell->position);

        // If cell is unique and correct
        if (IS_CHESS_POS_CELL_CORRECT(currCell->position) &&
            (board[row][col] == 0)) {
            board[row][col] = ++cellsCounter; // Mark its list place in the board
            // Continue to the next cell
            prevCell = currCell;
            currCell = currCell->next;
        } else { // If the cell is a duplicate or incorrect
            // Remove the cell from the list and continue to the next cell
            chessPosCell *cellToRemove = currCell;
            currCell = currCell->next;
            RemoveCellFromList(list, prevCell, cellToRemove);
        }}
}

void printColumnNumbers() {
    // Print the top row of column numbers
    printf("   ");
    for (int col = 1; col <= BOARD_SIZE; col++) {
        printf(" %d  ", col);
    }
    printf("\n");
}

void printTopBorder() {
    // Print the top border of the board
    printf(" ╔");
    for (int col = 0; col < BOARD_SIZE; col++) {
        printf("═══");
        if (col < BOARD_SIZE - 1) {
            printf("╦");
        } else {
            printf("╗");
        }
    }
    printf("\n");
}

void printRow(int* boardRow, int row) {
    // Print the row letter
    printf("%c║", 'A' + row);

    // Print the cells in the row
    for (int col = 0; col < BOARD_SIZE; col++) {
        if (boardRow[col] != 0) {
            printf("%2d ", boardRow[col]); // Center numbers in a 3-character field
        } else {
            printf("   "); // Maintain spacing for empty cells
        }
        printf("║");
    }
    printf("\n");
}


void printRowSeparator() {
    // Print the border between rows
    printf(" ╠");
    for (int col = 0; col < BOARD_SIZE; col++) {
        printf("═══");
        if (col < BOARD_SIZE - 1) {
            printf("╬");
        } else {
            printf("╣");
        }
    }
    printf("\n");
}

void printBottomBorder() {
    // Print the bottom border of the board
    printf(" ╚");
    for (int col = 0; col < BOARD_SIZE; col++) {
        printf("═══");
        if (col < BOARD_SIZE - 1) {
            printf("╩");
        } else {
            printf("╝");
        }
    }
    printf("\n");
}

void printBoard(int** boardToPrint) {
    printColumnNumbers();
    printTopBorder();

    for (int row = 0; row < BOARD_SIZE; row++) {
        printRow(boardToPrint[row], row);
        if (row < BOARD_SIZE - 1) {
            printRowSeparator();
        }
    }

    printBottomBorder();
}