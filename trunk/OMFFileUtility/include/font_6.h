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
} font6;

/**
*   Loads a font from file
*   WARNING: Free the pointer of the struct when you don't need it.
*/
font6 loadFont6(FILE *);

/**
*   Saves a font in a file at the position of the int
*/
void saveFont6(font6, FILE *,int);

/**
*   Prints a single character, with char representation and offset int
*/
void printFont6Letter(font6Letter,char,int);

/**
*   Prints a whole font:
*/
void printFont6(font6,int);

/**
*   Gains control of the program and converts it into a font8 editor.
*   That int is the offset of the file.
*   WARNING: The pointer of the struct returned is the same that the pointer given
*   as argument. So, don't free it unless you want to free the result's pointer.
*/
font6 font6Editor(font6, int);

#endif // FONT_6_H
