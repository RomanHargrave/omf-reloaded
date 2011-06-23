#ifndef OMFSOUNDS_H
#define OMFSOUNDS_H

#include <vector>
#include <fstream>

typedef unsigned int DWORD;

using namespace std;

struct sound_header
{
    DWORD start;
    DWORD end;
};

vector<sound_header> getAllSoundsInfo(ifstream & file);

#endif // OMFSOUNDS_H
