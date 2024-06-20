/**
 * @file KnightMoveCalculator.c
 *
 * @brief Calculates all possible knight moves from each position on a chessboard.
 *
 * This module generates a matrix of all valid moves a knight can make from any position on the chessboard.
 * The function allocates and returns a 3D array where each cell contains the valid moves for a knight
 * starting from that position. This functionality supports other modules by providing essential data
 * on possible knight movements for further path finding and analysis.
 */

#include "../include/macros.h"
#include "../include/typedefs.h"
#include "../include/prototypes.h"

/**
 * Generates a 3D array where each element contains all valid moves for a knight
 * from a given position on the chessboard.
 *
 * @return A pointer to a 3D array of chessPosArray structures containing valid knight moves.
 */
chessPosArray*** validKnightMoves() {
    chessPosArray*** board = (chessPosArray***)malloc(BOARD_SIZE * sizeof(chessPosArray**));
    if (board == NULL) {
        printf("Allocation error. #01");
        exit(1);
    }

    for (int i = 0; i < BOARD_SIZE; i++) {
        board[i] = (chessPosArray**)malloc(BOARD_SIZE * sizeof(chessPosArray*));
        if (board[i] == NULL) {
            printf("Allocation error. #02");
            exit(1);
        }
    }

    int baseMoves[8][2] = { {LEAPBELOW, RIGHT}, {LEFT, LEAPABOVE}, {RIGHT, LEAPABOVE},
                            {LEAPABOVE, RIGHT}, {LEAPABOVE, LEFT}, {RIGHT, LEAPBELOW},
                            {LEFT, LEAPBELOW}, {LEAPBELOW, LEFT} };

    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            chessPos* validPositions = (chessPos*)malloc(8 * sizeof(chessPos));
            int count = 0;

            if (validPositions == NULL) {
                printf("Allocation error. #03");
                exit(1);
            }

            for (int move = 0; move < 8; move++) {
                int newRow = row + baseMoves[move][0];
                int newCol = col + baseMoves[move][1];

                if (newRow >= 0 && newRow < BOARD_SIZE && newCol >= 0 && newCol < BOARD_SIZE) {
                    validPositions[count][0] = 'A' + newRow;
                    validPositions[count][1] = '1' + newCol;
                    count++;
                }
            }

            validPositions = (chessPos*)realloc(validPositions, count * sizeof(chessPos));
            chessPosArray* posArray = (chessPosArray*)malloc(sizeof(chessPosArray));
            if (posArray == NULL) {
                printf("Allocation error. #04");
                exit(1);
            }
            posArray->size = count;
            posArray->positions = validPositions;
            board[row][col] = posArray;
        }
    }
    return board;
}

/**
 * Frees the memory allocated for storing valid knight moves.
 *
 * @param validKnightMoves A 3D array of chessPosArray structures to be freed.
 */
void getFreed(chessPosArray*** validKnightMoves) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            free(validKnightMoves[i][j]->positions);
            free(validKnightMoves[i][j]);
        }
        free(validKnightMoves[i]);
    }
    free(validKnightMoves);
}
