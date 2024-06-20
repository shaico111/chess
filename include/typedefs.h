/**
 * @file typedefs.h
 *
 * @brief Defines types and structures used across the chessboard project.
 *
 * This file contains definitions for types and structures crucial for representing chess positions,
 * linked lists for knight movement paths, and other game state elements necessary for managing
 * the logic of chess games, especially focusing on the knight's legal moves and paths.
 */
#ifndef TYPEDEFS_H
#define TYPEDEFS_H

typedef int BOOL; // Defines a boolean type. Boolean values can be found as macros in macros.h

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

typedef struct _treeNodeList {
    struct _treeNodeListCell *head;
    struct _treeNodeListCell *tail;
} treeNodeList;

typedef struct _treeNode {
    chessPos position;
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
