#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <main.h>
#include <types.h>
#include <sprite_header.h>
#include <font_8.h>
#include <font_6.h>

int main(int argc, char ** argv)
{
    // Init file to parse to NULL
    fileToParse = NULL;

    argumentParser(argc, argv);
    if (fileToParse == NULL)
    {
        fprintf(stderr,"Error: no input file selected\n");
        showHelp();
    }
    else
    {
        FILE * pFile = fopen(fileToParse,"r+b");
        if (!pFile)
        {
            fprintf(stderr, "Error: selected file could not be opened.\n");
            return 0;
        }
        // Magic function here:
        parseFile(pFile);
        fclose(pFile);
    }


    return 0;
}

void showHelp()
{
    printf("One Must Fall File Format Utility %d.%d\n",MAJOR_VERSION,MINOR_VERSION);
    printf("Options:\n\n");

    printf("-h\t\t\t\tShow this help\n");
    printf("-i<file>\t\t\tFile to include\n");
    printf("-t<type file>\t\t\tKind of file to parse\n");
    printf("\tKind of files you can select are:\n");
    printf("\tsprite spriteh font8 font6\n");
    // Exit to stop the program doing anything else.
    exit(0);
}

void showCommandsHelp()
{
    if (SYSTEM_CLEAR)
    {
        printf("Error trying to clear screen.\n");
    }
    printf("Commands:\n");
    printf("show (gives information about the file you are watching)\n");
    printf("letters (shows letters of the font, only font8 or font6 mode)\n");
    printf("edit (gives you an interface to edit the file, only font8 or font6 mode)\n");
    printf("set (set a value in the file)\n");
    printf("exit (closes the editor you are in)\n");
    printf("help (shows this help) \n");
}

void optionParser(char * option)
{
    if (strcmp(option,"-h") == 0)
    {
        showHelp();
    }
    else if (option[1] == 'i')
    {
        fileToParse = option+2;
    }
    else if (option[1] == 't')
    {
        option+=2;
        if (strcmp(option,"sprite") == 0)
            fileType = SPRITE;
        else if (strcmp(option,"spriteh") == 0)
            fileType = SPRITE_HEADER;
        else if (strcmp(option,"font8") == 0)
            fileType = FONT_8;
        else if (strcmp(option,"font6") == 0)
            fileType = FONT_6;
    }

}

void argumentParser(int argc, char ** argv)
{
    int i;
    if (argc == 1)
    {
        showHelp();
        return;
    }
    for (i = 1; i < argc; i++)
    {
        /// Parse options:
        if (argv[i][0] == '-')
            optionParser(argv[i]);
    }
}

/// ----------------------- END OF UTILITY FUNCTIONS ---------------------------
/// -------------------  START OF FILE PARSING FUNCTIONS -----------------------

enum fileTypes detectFileType(FILE * pFile)
{
    // Sprite headers are always of size 12 bytes:
    // So, this can be a sprite header or empty sprite.
    if (fileSize(pFile) == 12)
        return SPRITE_HEADER;
    return AUTO;
}

void parseFile(FILE * pFile)
{
    if (fileType == AUTO)
        fileType = detectFileType(pFile);
    // Still unkown filetype
    if (fileType == AUTO)
    {
        fprintf(stderr,"Unkown file type. Please, select the file type you want to parse to force the program to parse it.");
        exit(0);
    }
    // Reading sprite header:
    else if (fileType == SPRITE_HEADER)
    {
        if (SYSTEM_CLEAR)
        {
            printf("Error trying to clear screen.\n");
        }
        sSpriteHeader s = loadSpriteHeader(pFile);
        s = spriteHeaderEditor(s,0);
        saveSpriteHeader(s,pFile,0);
    }
    else if (fileType == FONT_8)
    {
        if (SYSTEM_CLEAR)
        {
            printf("Error trying to clear screen.\n");
        }
        font8 f = loadFont8(pFile);
        f = font8Editor(f,0);
        saveFont8(f,pFile,0);
    }
    else if (fileType == FONT_6)
    {
        if (SYSTEM_CLEAR)
        {
            printf("Error trying to clear screen.\n");
        }
        font6 f = loadFont6(pFile);
        f = font6Editor(f,0);
        saveFont6(f,pFile,0);
    }
}

/// ------------------------ END OF FILE PARSING FUNCTIONS -----------------------
/// ------------------------ START OF GENERAL PURPOSE FUNCS -----------------------

void modifyValue(const char * kind, int pos, int value, void * mem)
{
    if (!strcmp(kind,"byte"))
    {
        if (value > 255)
        {
            printf("You can not write a value higher than 255 in a single byte");
        }
        else
        {
            BYTE * p = (void*)mem;
            p += pos;
            *p = value;
        }
    }
    else if (!strcmp(kind,"sbyte"))
    {
        if (value < -128 || value > 127)
        {
            printf("You can not write a value outside [-128,127] in a single signed byte");
        }
        else
        {
            char * p = (void*)mem;
            p += pos;
            *p = value;
        }
    }
    else if (!strcmp(kind,"word"))
    {
        if (value > 65535)
        {
            printf("You can not write a value higher than 65535 in a single word");
        }
        else
        {
            WORD * p = (void*)mem;
            p += pos;
            *p = value;
        }
    }
    else if (!strcmp(kind,"sword"))
    {
        if (value > 32767 || value < -32768)
        {
            printf("You can not write a value outside [-32768,32767] in a signed word");
        }
        else
        {
            short * p = (void*)mem;
            p += pos;
            *p = value;
        }
    }
    else if (!strcmp(kind,"dword"))
    {
        DWORD * p = (void*)mem;
        p += pos;
        *p = value;
    }
}

int fileSize(FILE * pFile)
{
    // Calculate size:
    fseek(pFile, 0L, SEEK_END);
    int sz = ftell(pFile);
    // Return to the beginning
    fseek(pFile, 0L, SEEK_SET);
    return sz;
}
