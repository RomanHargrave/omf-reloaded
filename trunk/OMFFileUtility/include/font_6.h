#ifndef FONT_6_H
#define FONT_6_H

#include <types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef BYTE font6Letter[6];
typedef struct
{
    int size;
    font6Letter * f;
} sFont6;

/**
*   Loads a font from file
*   WARNING: Free the pointer of the struct when you don't need it.
*/
sFont6 loadFont6(FILE *, int);

/**
*   Saves a font in a file at the position of the int
*/
void saveFont6(sFont6, FILE *,int);

/**
*   Destroys a font6
*/
void destroyFont6(sFont6);

/**
*   Prints a single character, with char representation and offset int
*/
void printFont6Letter(font6Letter,char,int);

/**
*   Prints a whole font:
*/
void printFont6(sFont6,int);

/**
*   Gains control of the program and converts it into a font8 editor.
*   That int is the offset of the file.
*   WARNING: The pointer of the struct returned is the same that the pointer given
*   as argument. So, don't free it unless you want to free the result's pointer.
*/
sFont6 font6Editor(sFont6, int);

#endif // FONT_6_H
