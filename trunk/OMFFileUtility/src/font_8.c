#include "font_8.h"

#include <main.h>

sFont8 loadFont8(FILE * pFile, int position)
{
    int backup = ftell(pFile);
    // Start at position:
    fseek(pFile,position,SEEK_SET);

    // Get size:
    int pointer = ftell(pFile);
    int sz = fileSize(pFile);

    // Restart position:
    fseek(pFile,pointer,SEEK_SET);

    // Check how much letters there are in this font:
    sz -= pointer;
    sz /= sizeof(font8Letter);

    // Allocate memory:
    sFont8 result;
    result.f = (font8Letter*)malloc(sizeof(font8Letter)*sz);
    result.size = sz;

    // Read letters:
    int r = fread(result.f,sizeof(font8Letter),sz,pFile);
    if (r != sz)
    {
        fprintf(stderr, "Error: couldn't read a font.\n");
        exit(0);
    }

    // return file to position:
    fseek(pFile,backup,SEEK_SET);

    return result;
}

void saveFont8(sFont8 f, FILE * pFile, int position)
{
    int backup = ftell(pFile);
    fseek(pFile,position,SEEK_SET);
    int w = fwrite(f.f,sizeof(font8Letter),f.size,pFile);
    if (f.size != w)
    {
        fprintf(stderr,"Error: couldn't write the font.\n");
        exit(0);
    }
    fseek(pFile,backup,SEEK_SET);
}

void printFont8Letter(font8Letter fl,char c, int offset)
{
    printf("0x%04X: %c\n",offset,c);
    int i;
    for (i = 0; i < 8; i++)
    {
        BYTE line = fl[i];
        int j;
        for (j = 0; j < 8; j++)
        {
            if (line&128)
                printf("#");
            else
                printf(" ");
            line <<= 1;
        }
        printf("\n");
    }
}

void printFont8(sFont8 f,int offset)
{
    int i;
    for (i = 0; i < f.size; i++)
    {
        printFont8Letter(f.f[i],32+i,offset + i*sizeof(font8Letter));
    }
}

sFont8 font8Editor(sFont8 in, int offset)
{
    sFont8 out = in;
    char action[512];
    while (strcmp(action,"exit"))
    {
        if (scanf("%s",action) == EOF)
        {
            printf("End of file found. Exiting.");
            break;
        }
        if (!strlen(action))
            continue;
        if (!strcmp(action,"show"))
        {
            printFont8(out,offset);
        }
        else if (!strcmp(action,"help"))
        {
            showCommandsHelp();
        }
        else if (!strcmp(action,"letters"))
        {
            scanf("%s",action);
            int i;
            for (i = 0; i < strlen(action);i++)
                printFont8Letter(out.f[action[i]-32],action[i],offset+(action[i]-32)*sizeof(font8Letter));
        }
        else if (!strcmp(action,"edit"))
        {
            printf("Write the letters you want to edit in a single word wihtout spaces:\n");
            printf("If you want to edit space symbol, just write \"\"\n");
            char characters[128];
            scanf("%s",characters);
            printf("Now write 8 lines of 8 characters each one, where\n");
            printf(". means blank space and # means occupied space:\n");
            // Edit space character:
            if (!strcmp(characters,"\"\""))
            {
                printf("Space:\n");
                int i;
                // 8 Lines:
                for (i = 0; i < 8; i++)
                {
                    // Get line:
                    scanf("%s",action);
                    int j;
                    // Set line to 0:
                    BYTE line = 0;
                    // Change 8 spaces of line:
                    for (j = 0; j < 8; j++)
                    {
                        line <<= 1;
                        line |= (action[j] == '#');
                    }
                    // Change line:
                    out.f[' '-32][i] = line;
                }
                printf("Successful edition. Your letter:\n");
                printFont8Letter(out.f[' '-32],' ',(' '-32)*sizeof(font8Letter)+offset);
            }
            // Any kind of characters:
            else
            {
                int k;
                // Each character of word:
                for (k = 0; k < strlen(characters); k++)
                {
                    char editting = characters[k];
                    printf("%c:\n",editting);
                    int i;
                    // 8 Lines:
                    for (i = 0; i < 8; i++)
                    {
                        // Get line:
                        scanf("%s",action);
                        // Set line to 0:
                        BYTE line = 0;
                        // Change 8 spaces of line:
                        int j;
                        for (j = 0; j < 8; j++)
                        {
                            line <<= 1;
                            line |= (action[j] == '#');
                        }
                        // Change line:
                        out.f[editting-32][i] = line;
                    }
                    printf("Successful edition. Your letter:\n");
                    printFont8Letter(out.f[editting-32],editting,(editting-32)*sizeof(font8Letter)+offset);
                }
            }
        }
        else if (!strcmp(action,"set"))
        {
            printf("You are in font mode. Please, use the command edit instead.\n");
        }
        else if (!strcmp(action,"save"))
        {
            char filename[128];
            scanf("%s",filename);
            FILE * pFile = fopen(filename,"wb");
            if (pFile)
            {
                saveFont8(out,pFile,0);
                fclose(pFile);
            }
            else
            {
                printf("Could not open or create %s file\n",filename);
            }
        }
        else
        {
            if (strcmp(action,"exit"))
                printf("Unkown command \"%s\". Write help to check command list.\n",action);
        }
    }
    return out;
}
