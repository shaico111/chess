/**
 * File: chessGameLogic.c
 * ----------------------
 * Implements the game logic for chess, focusing on knight movements.
 * Contains functions to compute valid moves and update board state.
 */

#include "../include/macros.h"
#include "../include/typedefs.h"
#include "../include/prototypes.h"

chessPosArray*** validKnightMoves() {
    chessPosArray*** board = (chessPosArray***)malloc(BOARD_SIZE * sizeof(chessPosArray**)); //allocate for BOARD_SIZE
    int i, row, col, count, move, newRow, newCol;

    if (board == NULL) //Allocation checkup.
    {
        printf("Allocation error. #01");
        exit(1);
    }

    for (i = 0; i < BOARD_SIZE; i++)
    {
        board[i] = (chessPosArray**)malloc(BOARD_SIZE * sizeof(chessPosArray*));

        if (board[i] == NULL) //checkup.
        {
            printf("Allocation error. #02");
            exit(1);
        }
    }

    int baseMoves[8][2] = {
            {LEAPABOVE, RIGHT},    // Two steps up, one step right
            {RIGHT, LEAPABOVE},    // One step up, two steps right
            {RIGHT, LEAPBELOW},    // One step down, two steps right
            {LEAPBELOW, RIGHT},    // Two steps down, one step right
            {LEAPBELOW, LEFT},     // Two steps down, one step left
            {LEFT, LEAPBELOW},     // One step down, two steps left
            {LEFT, LEAPABOVE},     // One step up, two steps left
            {LEAPABOVE, LEFT}      // Two steps up, one step left
    };


    for (row = 0; row < BOARD_SIZE; row++)
    {
        for (col = 0; col < BOARD_SIZE; col++)
        {
            chessPos* validPositions = (chessPos*)malloc(8 * sizeof(chessPos));
            count = 0;

            if (validPositions == NULL) //Allocation checkup
            {
                printf("Allocation error. #03");
                exit(1);
            }

            for (move = 0; move < 8; move++)
            {
                newRow = row + baseMoves[move][0];
                newCol = col + baseMoves[move][1];

                if (newRow >= 0 && newRow < BOARD_SIZE && newCol >= 0 && newCol < BOARD_SIZE)
                {
                    validPositions[count][0] = 'A' + newRow;
                    validPositions[count][1] = '1' + newCol;
                    count++;
                }
            }

            validPositions = (chessPos*)realloc(validPositions, count * sizeof(chessPos));

            chessPosArray* posArray = (chessPosArray*)malloc(sizeof(chessPosArray));

            if (posArray == NULL) // checkup
            {
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

void getFreed(chessPosArray*** validKnightMoves) {
    int i, j;

    for (i = 0; i < BOARD_SIZE; i++)
    {
        for (j = 0; j < BOARD_SIZE; j++)
        {
            free(validKnightMoves[i][j]->positions);
            free(validKnightMoves[i][j]);
        }
        free(validKnightMoves[i]);
    }
    free(validKnightMoves);
}
