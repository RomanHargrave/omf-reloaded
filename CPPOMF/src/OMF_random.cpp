#include <OMF_random.h>
#include <fstream>
#include <cassert>

typedef unsigned char BYTE;
typedef unsigned int DWORD;

// Extracted from:
// http://wtf.hijacked.us:8080/wiki/index.php/Random.dat_stuff

DWORD g_something;
BYTE g_randSeed1, g_randSeed2, g_randSeed3, g_randSeed4;
char g_randomTable[256];
bool initialized = false;

// This may be a global:
int g_flags = 0;

void OMF_randomSeed(unsigned int seed)
{
    char seed2 = g_randSeed2;
    if ( !(g_flags & 2) )
    {
        g_randSeed1 = seed >> 1;
        g_randSeed3 = seed >> 5;
        ++g_something;
        g_randSeed4 = seed >> 3;
        seed2 = (BYTE)g_something + 3 * (BYTE)seed;
        g_randSeed1 += 3 * (BYTE)g_something;
        g_randSeed4 += g_something >> 1;
        g_randSeed3 += 4 * (BYTE)g_something;
    }
    g_randSeed2 = seed2;
}

int OMF_random(int max)
{

  if ( !initialized )
  {
    std::ifstream ra("resources/original/random.dat");
    assert(ra.good());
    ra.read(g_randomTable,256);
    ra.close();
    initialized = true;
  }

  int result;
  if ( max <= 255 )
  {
    result = max * (g_randomTable[g_randSeed1] ^ g_randomTable[g_randSeed2] ^ (unsigned int)g_randomTable[g_randSeed3]) >> 8;
  }
  else if ( max <= 65535 )
  {
    result = max * (((g_randomTable[g_randSeed3] ^ g_randomTable[g_randSeed1] ^ g_randomTable[g_randSeed4]) << 8) | (g_randomTable[g_randSeed2] ^ g_randomTable[g_randSeed1] ^ (unsigned int)g_randomTable[g_randSeed3]) >> 16);
  }
  else
  {
    result = g_randomTable[g_randSeed4] ^ (((max >> 8) * (g_randomTable[g_randSeed3] ^ g_randomTable[g_randSeed1] ^ g_randomTable[g_randSeed2]) | ((unsigned int)g_randomTable[g_randSeed4] << 8)) >> 16 << 8);
  }
  g_randSeed1 -= 2;
  g_randSeed2 += 1;
  g_randSeed3 += 3;
  g_randSeed4 += 7;
  return result;
}
