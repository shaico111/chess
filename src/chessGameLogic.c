/**
 * File: chessGameLogic.c
 * ----------------------
 * Implements the game logic for chess, focusing on knight movements.
 * Contains functions to compute valid moves and update board state.
 */

#include "../include/macros.h"
#include "../include/typedefs.h"
#include "../include/prototypes.h"
chessPosArray*** validKnightMoves(void)
{
    chessPosArray*** board = (chessPosArray***)malloc(BOARD_SIZE * sizeof(chessPosArray**)); //allocate for BOARD_SIZE
    int i, row, col, count, move;

    if (board == NULL) //Allocation checkup.
    {
        printf("Allocation error. #01");
        exit(1);
    }

    for (i = 0; i < BOARD_SIZE; i++) //allocate for each.
    {
        board[i] = (chessPosArray**)malloc(sizeof(chessPosArray*));

        if (board[i] == NULL) //checkup.
        {
            printf("Allocation error. #02");
            exit(1);
        }
    }

    int baseMoves[8][2] = { {LEAPABOVE, RIGHT} ,{LEAPABOVE, LEFT} ,{LEAPBELOW, RIGHT}, {LEAPBELOW, LEFT},
        {RIGHT, LEAPABOVE},{RIGHT, LEAPBELOW}, {LEFT, LEAPABOVE}, {RIGHT, LEAPBELOW} }; //general basic knight moves.

    for (row = 0; row < BOARD_SIZE; row++)     //Iterate on each row { (A,0) -> (A, 8) }
    {
        for (col = 0; col < BOARD_SIZE; col++) //Iterate on each col { (A, 0) -> (H, 0) }
        {
            chessPos* validPositions = (chessPos*)malloc(8 * sizeof(chessPos)); //Allocate (for 8 moves tops).
            count = 0;

            if (validPositions == NULL) //Allocation checkup
            {
                printf("Allocation error. #03");
                exit(1);
            }

            for (move = 0; move < 8; move++) //Iterate on the 8 possible moves.
            {
                int newRow = row + baseMoves[move][0]; //calculation according to base moves (each move consists of change in row and col, therefor 2 actions.
                int newCol = col + baseMoves[move][1];

                if (newRow >= 0 && newRow < BOARD_SIZE && newCol >= 0 && newCol < BOARD_SIZE) //Add the data if the move is valid.
                {
                    validPositions[count][0] = 'A' + newRow;
                    validPositions[count][1] = '1' + newCol;
                    count++;                                                     //move counter each time we notice a possible move.
                }
            }

            validPositions = (chessPos*)realloc(validPositions, count * sizeof(chessPos)); //realloc from the 8, to the exact move counter;

            chessPosArray* posArray = (chessPosArray*)malloc(sizeof(chessPosArray));

            if (posArray == NULL) // checkup
            {
                printf("Allocation error. #04");
                exit(1);
            }

            posArray->size = count;              //save the amount of moves and validPos in teh struct.
            posArray->positions = validPositions;

            board[row][col] = posArray; //"connect" it before keeping iterating.
        }
    }
    return board; //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // BEN FIX NOTES BEFORE SENDING THE PROJECT. 
    // NOTES NEED
    //FORMAL MANNER.
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // MAYBE EVEN ADD AN ALLOCATION CHECKUP FUNC
}
void getFreed(chessPosArray*** validKnightMoves) //free...
{
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
