#include "../include/main.h"




//// Function to initialize the path tree with all possible moves for the knight
//pathTree *initializePathTreeWithRoot(chessPos initialPosition) {
//    pathTree *ptree = (pathTree *)malloc(sizeof(pathTree));
//    if (!ptree) {
//        fprintf(stderr, "Failed to allocate memory for path tree\n");
//        exit(1);
//    }
//
//    treeNode *rootNode = (treeNode *)malloc(sizeof(treeNode));
//    if (!rootNode) {
//        fprintf(stderr, "Failed to allocate memory for root node\n");
//        free(ptree);
//        exit(1);
//    }
//
//    // Set the initial position
//    rootNode->position[0] = initialPosition[0];
//    rootNode->position[1] = initialPosition[1];
//    rootNode->nextMoves = NULL;  // This should be populated with the valid moves from this position
//
//    // Since we are testing, we can manually set this or use a function to determine valid moves
//    rootNode->nextMoves = validKnightMoves(); // This would realistically be more complex
//
//    ptree->root = rootNode;
//    return ptree;
//}

//// Function to display the path
//void printPath(chessPosList *path) {
//    if (!path || !path->head) {
//        printf("No valid path found.\n");
//        return;
//    }
//
//    chessPosCell *current = path->head;
//    while (current != NULL) {
//        printf("(%c, %c) -> ", current->position[0], current->position[1]);
//        current = current->next;
//    }
//    printf("End\n");
//}

int main() {
    // Initialize the game state
    chessPos initialPos = {'A', '1'};

    // Initialize the path tree
    pathTree *gameTree = initializePathTreeWithRoot(initialPos);

    // Find a path that covers all board
    chessPosList *resultPath = findKnightPathCoveringAllBoard(gameTree);

    // Print the path
    printPath(resultPath);

    // Free resources (not implemented here, should be handled appropriately)
    // freePathTree(gameTree);
    // freePath(resultPath);

    return 0;
}