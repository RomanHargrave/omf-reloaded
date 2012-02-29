#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <cstdio>
#include <cstdlib>

/**
*   This file contains general algorithms.
*/

/**
*   This function returns a pointer with memory
*   of the file specified.
*   NOTE: The pointer returned will not be freed, so do it yourself!
*/
void * falloc(const char * fileName);

#endif // ALGORITHM_H
