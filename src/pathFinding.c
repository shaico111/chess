/**
 * File: pathFinding.c
 * --------------------
 * Algorithms to find paths on the chessboard that a knight can follow.
 * These include finding all possible paths and optimal paths covering all squares.
 */

#include "../include/typedefs.h"
#include "../include/prototypes.h"
#include "../include/macros.h"

// Helper function to log positions for debugging
void logPosition(const char* prefix, chessPos position) {
    printf("%s: (%c, %c)\n", prefix, position[0], position[1]);
}

// Validating position within chess board limits
BOOL isPositionValid(chessPos position) {
    return position[0] >= 'A' && position[0] < 'A' + BOARD_SIZE &&
           position[1] >= '1' && position[1] < '1' + BOARD_SIZE;
}


treeNodeList* generateValidMoves(chessPos position, int depth, BOOL visited[BOARD_SIZE][BOARD_SIZE]) {
    if (depth > 2 * BOARD_SIZE) { // Limiting recursion depth
        return NULL;
    }

    int row = position[0] - 'A';
    int col = position[1] - '1';

    if (visited[row][col]) {
        return NULL;
    }

    visited[row][col] = TRUE; // Mark this position as visited
    treeNodeList* movesList = malloc(sizeof(treeNodeList));
    movesList->head = movesList->tail = NULL;

    int moveOffsets[8][2] = {{2, 1}, {1, 2}, {-1, 2}, {-2, 1}, {-2, -1}, {-1, -2}, {1, -2}, {2, -1}};
    for (int i = 0; i < 8; i++) {
        int newRow = row + moveOffsets[i][0];
        int newCol = col + moveOffsets[i][1];
        if (newRow >= 0 && newRow < BOARD_SIZE && newCol >= 0 && newCol < BOARD_SIZE) {
            chessPos newPos = {'A' + newRow, '1' + newCol};
            if (!visited[newRow][newCol]) {
                treeNode* newNode = malloc(sizeof(treeNode));
                newNode->position[0] = newPos[0];
                newNode->position[1] = newPos[1];
                newNode->nextMoves = generateValidMoves(newPos, depth + 1, visited);

                treeNodeListCell* newCell = malloc(sizeof(treeNodeListCell));
                newCell->node = newNode;
                newCell->next = NULL;
                if (!movesList->head) {
                    movesList->head = movesList->tail = newCell;
                } else {
                    movesList->tail->next = newCell;
                    movesList->tail = newCell;
                }
            }
        }
    }

    visited[row][col] = FALSE; // Unmark this position
    return movesList;
}

void printPath(chessPosList* path) {
    if (!path || !path->head) {
        printf("No valid path found.\n");
        return;
    }

    chessPosCell* current = path->head;
    while (current) {
        printf("(%c, %c) -> ", current->position[0], current->position[1]);
        current = current->next;
    }
    printf("End\n");
}

// Helper function to check if all board positions are covered
static BOOL allPositionsCovered(BOOL visited[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (!visited[i][j])
                return FALSE;
        }
    }
    return TRUE;
}

// Recursive function to try to find a valid knight's path
// Recursive function to try to find a valid knight's path
static BOOL findPath(treeNode *node, BOOL visited[BOARD_SIZE][BOARD_SIZE], chessPosList *path, chessPosArray ***moves) {
    if (!isPositionValid(node->position)) {
        logPosition("Invalid position accessed", node->position);
        return FALSE; // Guard against invalid positions
    }

    int row = CELL_TO_ROW(node->position);
    int col = CELL_TO_COL(node->position);

    if (visited[row][col]) {
        logPosition("Revisited position", node->position);
        return FALSE; // Early exit if position was already visited
    }

    // Mark the current position as visited
    visited[row][col] = TRUE;
    addPositionToPath(path, node->position);
    logPosition("Visiting position", node->position);

    if (allPositionsCovered(visited)) {
        return TRUE; // Success if all positions are covered
    }

    chessPosArray *possibleMoves = moves[row][col];
    for (int i = 0; i < possibleMoves->size; i++) {
        if (isPositionValid(possibleMoves->positions[i])) {
            treeNode nextNode = {possibleMoves->positions[i], NULL}; // Simplified node initialization
            if (findPath(&nextNode, visited, path, moves)) {
                return TRUE;
            }
        }
    }

    // Backtrack if no valid path found from current position
    visited[row][col] = FALSE;
    removeLastPositionFromPath(path);
    logPosition("Backtracking from position", node->position);
    return FALSE;
}

// Main function to find a knight's path covering all board
chessPosList *findKnightPathCoveringAllBoard(pathTree *path_tree) {
    if (!path_tree || !path_tree->root) return NULL;

    BOOL visited[BOARD_SIZE][BOARD_SIZE] = {0};
    chessPosList *path = malloc(sizeof(chessPosList));
    if (!path) return NULL;
    path->head = path->tail = NULL;

    // Get all valid knight moves
    chessPosArray ***moves = validKnightMoves();

    // Start the path finding from the root node
    if (findPath(path_tree->root, visited, path, moves)) {
        getFreed(moves); // Free the moves array
        return path;
    }

    // Clean up if no valid path is found
    freePath(path);
    getFreed(moves);
    return NULL;
}

BOOL addPositionToPath(chessPosList* path, chessPos position) {
    if (!isPositionValid(position)) {
        return FALSE;
    }

    chessPosCell* newCell = malloc(sizeof(chessPosCell));
    if (!newCell) {
        printf("Memory allocation failed\n");
        return FALSE;
    }
    newCell->position[0] = position[0];
    newCell->position[1] = position[1];
    newCell->next = NULL;

    if (!path->head) {
        path->head = path->tail = newCell;
    } else {
        path->tail->next = newCell;
        path->tail = newCell;
    }

    return TRUE;
}

void freePath(chessPosList* path) {
    chessPosCell* current = path->head;
    chessPosCell* next;
    while (current) {
        next = current->next;
        free(current);
        current = next;
    }
    free(path);
}



void removeLastPositionFromPath(chessPosList* path) {
    if (!path->head) return;

    if (path->head == path->tail) {
        free(path->head);
        path->head = path->tail = NULL;
    } else {
        chessPosCell* current = path->head;
        while (current->next != path->tail) {
            current = current->next;
        }
        free(path->tail);
        path->tail = current;
        path->tail->next = NULL;
    }
}

pathTree* initializePathTreeWithRoot(chessPos initialPosition) {
    pathTree* ptree = malloc(sizeof(pathTree));
    if (!ptree) {
        printf("Failed to allocate memory for path tree\n");
        return NULL;
    }

    treeNode* rootNode = malloc(sizeof(treeNode));
    if (!rootNode) {
        printf("Failed to allocate memory for root node\n");
        free(ptree);
        return NULL;
    }

    rootNode->position[0] = initialPosition[0];
    rootNode->position[1] = initialPosition[1];
    BOOL visited[BOARD_SIZE][BOARD_SIZE] = {{FALSE}};
    rootNode->nextMoves = generateValidMoves(rootNode->position, 0, visited);

    ptree->root = rootNode;
    return ptree;
}

