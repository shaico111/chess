/**
 * @file main.c
 *
 * @brief Executes the main program logic to find a complete knight's tour on a 5x5 chess board.
 *
 * Initializes the chess board and handles user inputs for the starting position of the knight. It then
 * validates this starting position, generates all possible knight paths from this position, and attempts
 * to find a complete path covering the entire board. If a path is found, it is displayed; otherwise, a
 * message indicating failure is shown. Memory cleanup is performed before program termination to avoid
 * leaks.
 *
 * @authors
 * Ben Vaanunu
 * Shai Cohen
 */

#include "typedefs.h"
#include "prototypes.h"
#include <stdio.h>

int main() {
    chessPos startingPosition;  ///< Holds the starting position as entered by the user.
    char startColumn;           ///< Stores the column component of the starting position.
    int startRow;               ///< Stores the row component of the starting position.

    // Prompt user for input and validate it
    printf("Enter a starting position (e.g., A1): ");
    scanf(" %c%d", &startColumn, &startRow);
    startingPosition[0] = startColumn;
    startingPosition[1] = '0' + startRow;  // Convert integer row to character representation.

    // Check if the position is valid on a 5x5 chess board
    if (!isPositionValid(startingPosition)) {
        printf("Invalid input\n");
        return 1;  // Exit with error code 1 if the position is invalid.
    }

    // Generate all possible knight paths from the starting position
    pathTree possibleKnightPaths = findAllPossibleKnightPaths(&startingPosition);

    // Find a knight path covering all board
    chessPosList *completeKnightPath = findKnightPathCoveringAllBoard(&possibleKnightPaths);

    // Display the complete path if it exists
    if (completeKnightPath != NULL) {
        printf("A complete path covering all the board was found:\n");
        display(completeKnightPath);  // Display the complete path.
        freePath(completeKnightPath); // Free the path after displaying.
    } else {
        printf("No knight's tour.\n");
    }

    // Clean up the path tree to avoid memory leaks
    freePathTree(possibleKnightPaths);

    return 0;  // Exit with code 0 on successful completion.
}
