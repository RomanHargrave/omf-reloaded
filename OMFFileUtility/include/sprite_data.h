#ifndef SPRITE_DATA_H
#define SPRITE_DATA_H

#include <types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int size;
    BYTE * data;
} spriteData;

/**
*   Loads the sprite data from file
*/
spriteData loadSpriteData(FILE *, int, int);
/**
*   Saves the sprite data.
*/
void saveSpriteData(spriteData,FILE *,int);
/**
*   Destroys the sprite data.
*/
void destroySpriteData(spriteData);
/**
*   Prints info about sprite data
*/
void printSpriteData(spriteData,int offset);
/**
*   Gains control of the program and converts it into a sprite data editor.
*   That int is the offset of the file.
*/
spriteData spriteDataEditor(spriteData,int);

#endif // SPRITE_DATA_H
