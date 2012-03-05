#ifndef SPRITE_H
#define SPRITE_H

#include <types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sprite_header.h>
#include <sprite_data.h>

typedef struct
{
    sSpriteHeader header;
    spriteData imageData;
} sSprite;

/**
*   Loads a sprite from file
*/
sSprite loadSprite(FILE *, int);
/**
*   Saves a sprite
*/
void saveSprite(sSprite,FILE *,int);
/**
*   Prints sprite info
*/
void printSprite(sSprite,int offset);
/**
*   Gains control of the program and converts it into a sprite editor.
*   That int is the offset of the file.
*/
sSprite spriteEditor(sSprite,int);

#endif // SPRITE_H
