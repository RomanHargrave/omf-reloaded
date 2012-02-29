#include <algorithm.h>

void * falloc(const char * fileName)
{
    void * result = NULL;

    FILE * f = fopen(fileName,"rb");
    if (f != NULL)
    {
        // Calculate size:
        fseek(f, 0L, SEEK_END);
        int sz = ftell(f);
        // Return to the beginning
        fseek(f, 0L, SEEK_SET);

        result = malloc(sz);

        // Copy contents of the file in memory:
        fread(result,sz,1,f);

        // Close file
        fclose(f);
    }
    return result;
}
