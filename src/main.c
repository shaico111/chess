#include "../include/typedefs.h"
#include "../include/prototypes.h"
#include "../include/macros.h"
#include <stdio.h>

int main() {
    chessPos startingPosition;
    char col;
    int row;

    // Prompt user for input and validate it
    printf("Enter a starting position (e.g., A1): ");
    scanf(" %c%d", &col, &row);
    startingPosition[0] = col;
    startingPosition[1] = '0' + row;  // Convert int row to char

    // Check if the position is valid on a 5x5 chess board
    if (!isPositionValid(startingPosition)) {
        printf("Invalid position. Please enter a position like A1, within A-E and 1-5.\n");
        return 1;
    }

    // Generate all possible knight paths from the starting position
    pathTree knightPaths = findAllPossibleKnightPaths(&startingPosition);

    // Find a knight path covering all board
    chessPosList *completePath = findKnightPathCoveringAllBoard(&knightPaths);

    // Display the complete path if it exists
    if (completePath != NULL) {
        printf("A complete path covering all the board was found:\n");
        display(completePath);  // Assuming display function takes care of printing the entire board
        freePath(completePath); // Free the path after displaying
    } else {
        printf("No complete path covering all the board was found.\n");
    }

    // Clean up the path tree to avoid memory leaks
    freePathTree(knightPaths);

    return 0;
}
