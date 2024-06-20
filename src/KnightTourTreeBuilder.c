/**
 * @file KnightTourTreeBuilder.c
 *
 * @brief Constructs a tree of all possible knight paths starting from a given position on a chessboard.
 *
 * This file provides functionality to build a path tree illustrating potential knight tours from a
 * specified starting position on a chessboard. It uses depth-first search (DFS) to recursively explore
 * all moves and track the tour using a tree structure. The functions manage memory for dynamically allocated
 * structures and ensure all possible paths are explored efficiently.
 */

#include "../include/macros.h"
#include "../include/typedefs.h"
#include "../include/prototypes.h"

/**
 * Generates a path tree starting from a specified knight position on the chessboard.
 * Each path is explored recursively, and all possible moves are cataloged in a tree structure.
 *
 * @param startingPos The starting position of the knight on the chessboard.
 * @return A tree representing all possible paths from the starting position.
 */
pathTree findAllPossibleKnightPaths(chessPos* startingPos) {
    chessPosArray*** knightMoves = validKnightMoves(); // Retrieve all valid knight moves.
    pathTree tr;
    tr.root = createNode(*startingPos); // Create the root node of the path tree.

    chessPos path[BOARD_SIZE * BOARD_SIZE];
    path[0][0] = startingPos[0][0];
    path[0][1] = startingPos[0][1];

    BOOL visited[BOARD_SIZE][BOARD_SIZE] = { FALSE };
    buildPathTree(tr.root, knightMoves, visited, path, 1); // Recursively build the path tree.

    // Free the memory allocated for knight moves
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            free(knightMoves[i][j]->positions);
            free(knightMoves[i][j]);
        }
        free(knightMoves[i]);
    }
    free(knightMoves);

    return tr;
}

/**
 * Creates a new tree node for a given chess position.
 *
 * @param pos The chess position to create a node for.
 * @return A pointer to the newly created tree node.
 */
treeNode* createNode(chessPos pos) {
    treeNode* node = (treeNode*)malloc(sizeof(treeNode));
    if (node == NULL) {
        printf("Allocation error. #05\n");
        exit(1);
    }

    node->position[0] = pos[0];
    node->position[1] = pos[1];
    node->next_possible_positions.head = NULL;
    node->next_possible_positions.tail = NULL;
    return node;
}

/**
 * Frees all memory associated with the path tree.
 *
 * @param tree The path tree to free.
 */
void freePathTree(pathTree tree) {
    freeTreeNode(tree.root);
}

/**
 * Frees a tree node and all its child nodes recursively.
 *
 * @param node The node to free.
 */
void freeTreeNode(treeNode* node) {
    if (node == NULL) {
        return;
    }

    treeNodeListCell* curr = node->next_possible_positions.head;

    while (curr != NULL) {
        treeNodeListCell* next = curr->next;
        freeTreeNode(curr->node);
        free(curr);
        curr = next;
    }
    free(node);
}

/**
 * Adds a new node to the list of possible next positions in a path.
 *
 * @param lst The list to add the node to.
 * @param node The node to add.
 */
void addNodeToList(treeNodeList* lst, treeNode* node) {
    treeNodeListCell* newCell = (treeNodeListCell*)malloc(sizeof(treeNodeListCell));
    if (newCell == NULL) {
        printf("Allocation error. #06\n");
        exit(1);
    }

    newCell->node = node;
    newCell->next = NULL;

    if (lst->head == NULL) {
        lst->head = newCell;
        lst->tail = newCell;
    } else {
        lst->tail->next = newCell;
        lst->tail = newCell;
    }
}

/**
 * Recursively builds the path tree by exploring each valid knight move and adding it to the current path
 * if it hasn't been visited yet.
 *
 * @param curr Current node in the path tree.
 * @param knightMoves 3D array of all possible knight moves.
 * @param visited 2D array tracking visited positions.
 * @param path Array representing the current path.
 * @param pathSize Size of the current path.
 */
void buildPathTree(treeNode* curr, chessPosArray*** knightMoves, BOOL visited[BOARD_SIZE][BOARD_SIZE], chessPos* path, unsigned int pathSize) {
    int row = curr->position[0] - 'A';
    int col = curr->position[1] - '1';
    chessPosArray* possibleMoves = knightMoves[row][col];

    visited[row][col] = TRUE;

    for (int i = 0; i < possibleMoves->size; i++) {
        int newRow = possibleMoves->positions[i][0] - 'A';
        int newCol = possibleMoves->positions[i][1] - '1';

        if (!visited[newRow][newCol]) {
            treeNode* childNode = createNode(possibleMoves->positions[i]);
            addNodeToList(&curr->next_possible_positions, childNode);

            path[pathSize][0] = childNode->position[0];
            path[pathSize][1] = childNode->position[1];
            buildPathTree(childNode, knightMoves, visited, path, pathSize + 1);
        }
    }

    visited[row][col] = FALSE;
}
