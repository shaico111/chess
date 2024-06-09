/* File: macros.h
 * -----------------
 * This header file includes macro definitions used throughout the chessboard
 * project. It defines macros for boolean operations and other utility macros.
 */

#ifndef MACROS_H
#define MACROS_H
#include <stddef.h>     // Include macros.
#include <stdlib.h>    // Include standard library.
#include <stdio.h>

#define BOARD_SIZE 5 // Board width and height

#define CHAR_POSITION(c) ((c) - 'A' + 1) // Returns character's alphabet position.
#define CHAR_TO_DIGIT(c) ((c) - '0') // Converts a character digit to its numeric value.

// Macro to check if a given chess position is within the board boundaries
#define IS_CHESS_POS_CELL_CORRECT(pos) \
    (((CHAR_POSITION((pos)[0]) <= BOARD_SIZE) && (CHAR_POSITION((pos)[0]) > 0)) && \
     ((CHAR_TO_DIGIT((pos)[1]) <= BOARD_SIZE) && (CHAR_TO_DIGIT((pos)[1]) > 0)))

// Macro to convert chessPosCell position to row index in an array
#define CELL_TO_ROW(pos) (CHAR_POSITION((pos)[0]) - 1)

// Macro to convert chessPosCell position to column index in an array
#define CELL_TO_COL(pos) (CHAR_TO_DIGIT((pos)[1]) - 1)


#endif // MACROS_H
