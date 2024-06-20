/**
 * @file macros.h
 *
 * @brief Contains macro definitions to support chessboard logic operations.
 *
 * This file includes macros that simplify the operations within the chessboard project, such as
 * determining board sizes, move legality, and utility macros that aid in position translations and checks.
 *
 * @authors
 * Ben Vaanunu
 * Shai Cohen
 */
#ifndef MACROS_H
#define MACROS_H
#include <stddef.h> // Standard definition inclusion for size_t, etc.
#include <stdlib.h> // Standard library inclusion for dynamic memory management.
#include <stdio.h>  // Standard I/O functions inclusion.

#define BOARD_SIZE 5

// Directions
#define LEAPABOVE 2
#define LEAPBELOW -2
#define RIGHT 1
#define LEFT -1

// Boolean Values
#define TRUE 1
#define FALSE 0

#define CHAR_POSITION(c) ((c) - 'A' + 1) // Converts character to board position index.
#define CHAR_TO_DIGIT(c) ((c) - '0')     // Converts character to its integer digit.

// Checks if a given chess position is within the boundaries of the board
#define IS_CHESS_POS_CELL_CORRECT(pos) \
    (((CHAR_POSITION((pos)[0]) <= BOARD_SIZE) && (CHAR_POSITION((pos)[0]) > 0)) && \
     ((CHAR_TO_DIGIT((pos)[1]) <= BOARD_SIZE) && (CHAR_TO_DIGIT((pos)[1]) > 0)))

// Converts a chess position to a row index
#define CELL_TO_ROW(pos) (CHAR_POSITION((pos)[0]) - 1)

// Converts a chess position to a column index
#define CELL_TO_COL(pos) (CHAR_TO_DIGIT((pos)[1]) - 1)

#endif // MACROS_H
