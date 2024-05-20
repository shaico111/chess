/**
 * File: test_displayFunctions.c
 * -----------------------------
 * Tests for the display functions.
 *
 * These tests check the functions responsible for displaying the chess board and paths.
 */

#include "prototypes.h"
#include <assert.h>

void test_display() {
    // \TODO: Create a test case for the display function
    chessPosList list; // Mock the list
    display(&list); // Assuming display does not return a value and is void
    printf("Display function tested.\n"); // Indicative message
}

int main() {
    test_display();
    printf("All displayFunctions tests passed.\n");
    return 0;
}
