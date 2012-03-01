#include <limits.h>
typedef unsigned char BYTE;
typedef unsigned short WORD;
#if (UINT_MAX == 65535)
typedef unsigned long DWORD;
#else
typedef unsigned int DWORD;
#endif
