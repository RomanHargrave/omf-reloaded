#ifndef MAIN_H
#define MAIN_H

/// Constant definitions:
#define MAJOR_VERSION 0
#define MINOR_VERSION 2

/// Macros:
#if __unix
#define SYSTEM_CLEAR system("clear")
#endif

enum fileTypes
{
    AUTO,SPRITE_HEADER,SPRITE_DATA,SPRITE,FONT_8, FONT_6
} fileType;

char * fileToParse;

/**
*   It modifies the value of the void pointer at int position giving int value. char * can be:
*   byte sbyte word sword dword
*/
void modifyValue(const char * ,int,int,void*);

/**
*   It parses all arguments.
*/
void argumentParser(int,char**);
/**
*   It parses a single option.
*/
void optionParser(char *);
/**
*   Shows help of arguments to be passed to program.
*/
void showHelp();

/**
*   Shows help of the commands you can use within program.
*/
void showCommandsHelp();

/**
*   Function to parse the file. This is where the magic starts.
*/
void parseFile(FILE *);

/**
*   If fileType is AUTO, this function try to detect file type
*/
enum fileTypes detectFileType(FILE *);

/**
*   Returns the size of a file in bytes.
*   WARNING: This function restart the seek pointer to start.
*/
int fileSize(FILE *);

#endif // MAIN_H
