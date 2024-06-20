#include "../include/typedefs.h"
#include "../include/prototypes.h"
#include "../include/macros.h"

pathTree findAllPossibleKnightPaths(chessPos* startingPos) {
    int i, j;
    chessPosArray*** knightMoves = validKnightMoves();
    pathTree tr;
    tr.root = createNode(*startingPos);

    chessPos path[BOARD_SIZE * BOARD_SIZE];
    path[0][0] = startingPos[0][0];
    path[0][1] = startingPos[0][1];

    BOOL visited[BOARD_SIZE][BOARD_SIZE] = { FALSE };

    buildPathTree(tr.root, knightMoves, visited, path, 1);

    // Free the memory allocated for knight moves
    for (i = 0; i < BOARD_SIZE; i++)
    {
        for (j = 0; j < BOARD_SIZE; j++)
        {
            free(knightMoves[i][j]->positions);
            free(knightMoves[i][j]);
        }
        free(knightMoves[i]);
    }
    free(knightMoves);

    return tr;
}
treeNode* createNode(chessPos pos) { //Creates a new tree node.
    treeNode* node = (treeNode*)malloc(sizeof(treeNode));

    if (node == NULL)
    {
        printf("Allocation error. #05\n");
        exit(1);
    }

    node->position[0] = pos[0];
    node->position[1] = pos[1];
    node->next_possible_positions.head = NULL;
    node->next_possible_positions.tail = NULL;
    return node;
}
void freePathTree(pathTree tree) {
    freeTreeNode(tree.root);
}
void freeTreeNode(treeNode* node) {
    if (node == NULL)
    {
        return;
    }

    treeNodeListCell* curr = node->next_possible_positions.head;

    while (curr != NULL)
    {
        treeNodeListCell* next = curr->next;
        freeTreeNode(curr->node);
        free(curr);
        curr = next;
    }
    free(node);
}
void addNodeToList(treeNodeList* lst, treeNode* node) { //Adds a node to the linked lst
    treeNodeListCell* newCell = (treeNodeListCell*)malloc(sizeof(treeNodeListCell));
    if (newCell == NULL)
    {
        printf("Allocation error. #06\n");
        exit(1);
    }
    newCell->node = node;
    newCell->next = NULL;

    if (lst->head == NULL)
    {
        lst->head = newCell;
        lst->tail = newCell;
    }
    else
    {
        lst->tail->next = newCell;
        lst->tail = newCell;
    }
}
BOOL posInPath(chessPos* path, unsigned int size, chessPos pos) {
    int i;

    for (i = 0; i < size; i++)
    {
        if (path[i][0] == pos[0] && path[i][1] == pos[1])
        {
            return TRUE;
        }
    }

    return FALSE;
}
void buildPathTree(treeNode* curr, chessPosArray*** knightMoves, BOOL visited[BOARD_SIZE][BOARD_SIZE], chessPos* path, unsigned int pathSize) {
    int row, col, i, newRow, newCol;
    row = curr->position[0] - 'A';
    col = curr->position[1] - '1';
    chessPosArray* possibleMoves = knightMoves[row][col];

    visited[row][col] = TRUE;

    for (i = 0; i < possibleMoves->size; i++)
    {
        newRow = possibleMoves->positions[i][0] - 'A';
        newCol = possibleMoves->positions[i][1] - '1';

        if (!visited[newRow][newCol])
        {
            treeNode* childNode = createNode(possibleMoves->positions[i]);
            addNodeToList(&curr->next_possible_positions, childNode);

            path[pathSize][0] = childNode->position[0];
            path[pathSize][1] = childNode->position[1];
            buildPathTree(childNode, knightMoves, visited, path, pathSize + 1);
        }
    }

    visited[row][col] = FALSE;
}