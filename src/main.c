/**
 * File: main.c
 * -------------
 * Entry point for the chess knight movement simulation.
 * Handles user interactions and initializes the game logic.
 *
 * Section #5 (Main)
 */

#include "../include/main.h"

// Function to create a new chess position cell
chessPosCell *createNewCell(char pos[2], chessPosCell *next) {
    chessPosCell *newCell = (chessPosCell *)malloc(sizeof(chessPosCell));
    if (newCell == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    newCell->position[0] = pos[0];
    newCell->position[1] = pos[1];
    newCell->next = next;
    return newCell;
}

// Function to insert a new cell at the end of the list
void insertCellToEndList(chessPosList *list, char pos[2]) {
    chessPosCell *newCell = createNewCell(pos, NULL);
    if (list->tail == NULL) {
        list->head = newCell;
        list->tail = newCell;
    } else {
        list->tail->next = newCell;
        list->tail = newCell;
    }
}

// Function to create and populate a chessPosList with sample values
chessPosList *createSampleList() {
    chessPosList *list = (chessPosList *)malloc(sizeof(chessPosList));
    if (list == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    list->head = NULL;
    list->tail = NULL;

    // Sample positions to add to the list
    char positions[][2] = {
            {'A', '1'}, {'B', '2'}, {'C', '3'}, {'D', '4'}, {'E', '5'}
    };

    int numPositions = sizeof(positions) / sizeof(positions[0]);

    for (int i = 0; i < numPositions; i++) {
        insertCellToEndList(list, positions[i]);
    }

    return list;
}

int main() {
    // Create a sample list
    chessPosList *list = createSampleList();

    // Print the list to verify
    chessPosCell *curr = list->head;
    while (curr != NULL) {
        printf("%c%c -> ", curr->position[0], curr->position[1]);
        curr = curr->next;
    }
    printf("NULL\n");
    display(list);
    // Free the list
    curr = list->head;
    while (curr != NULL) {
        chessPosCell *toFree = curr;
        curr = curr->next;
        free(toFree);
    }
    free(list);

    return 0;
}