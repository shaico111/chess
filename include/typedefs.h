/* File: typedefs.h
 * -----------------
 * This header file includes type definitions used throughout the chessboard
 * project. It defines structures for representing chess positions and linked lists
 * that are fundamental to storing knight movement paths and other game states.
 */

#ifndef TYPEDEFS_H
#define TYPEDEFS_H

typedef int BOOL; // Defines a boolean type for the Hash typedef

typedef char chessPos[2];  // Stores a position on the chessboard as two characters.

typedef struct _chessPosArray {
    unsigned int size;      // Number of positions in the array.
    chessPos *positions;    // Array of chess positions.
} chessPosArray;

typedef struct _chessPosCell {
    chessPos position;          // The position of a chess piece.
    struct _chessPosCell *next; // Pointer to the next cell in the list.
} chessPosCell;

typedef struct _chessPosList {
    chessPosCell *head; // Head of the list of positions.
    chessPosCell *tail; // Tail of the list of positions.
} chessPosList;

typedef  struct  _treeNodeList {
    struct _treeNodeListCell  *head;
    struct _treeNodeListCell  *tail;
} treeNodeList;

typedef struct _treeNode{
    chessPos   position;
    treeNodeList next_possible_positions;
} treeNode;

typedef struct _treeNodeListCell {
    treeNode *node;                    // Pointer to a treeNode.
    struct _treeNodeListCell *next;    // Next possible position in the list.
} treeNodeListCell;

typedef struct _pathTree {
    treeNode *root;  // Root of the path tree.
} pathTree;


#endif // TYPEDEFS_H