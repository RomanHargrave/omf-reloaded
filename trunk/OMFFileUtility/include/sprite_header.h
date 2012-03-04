#ifndef SPRITE_HEADER_H
#define SPRITE_HEADER_H

#include <types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    BYTE length;
    short x;
    short y;
    WORD width;
    WORD height;
    BYTE index;
    BYTE dataMissing;
} sSpriteHeader;

/**
*   Loads a sprite header from file
*/
sSpriteHeader loadSpriteHeader(FILE *);
/**
*
*/
void saveSpriteHeader(sSpriteHeader,FILE *,int);
/**
*   Prints a sprite header
*/
void printSpriteHeader(sSpriteHeader,int offset);
/**
*   Gains control of the program and converts it into a sprite header editor.
*   That int is the offset of the file.
*/
sSpriteHeader spriteHeaderEditor(sSpriteHeader,int);

#endif // SPRITE_HEADER_H
