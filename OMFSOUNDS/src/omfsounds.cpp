#include <iostream>
#include <omfsounds.h>

vector<sound_header> getAllSoundsInfo(ifstream & file)
{
    vector<sound_header> result;
    // The size of the header, N, is :
    DWORD N;
    // Ignore the start of the header, as it starts on 0
    file.ignore(sizeof(DWORD));
    // Get size:
    file.read((char*)&N, sizeof(DWORD));
    // N is where ends header, and so where starts first sound:
    sound_header tmp;
    tmp.start = N;
    // Calculate number of sounds:
    // N/2DWORD-1
    result = vector<sound_header>((N/sizeof(sound_header)-1));
    // Extract all sounds info:
    for (size_t i = 0; i < result.size(); i++)
    {
        file.read((char*)&tmp.end, sizeof(DWORD));
        tmp.end--;
        result[i] = tmp;
        cerr << "Sound " << i+1 << " is on " << tmp.start << " until " << tmp.end;
        if (tmp.end == tmp.start + 1)
            cerr << " and it is empty";
        cerr << endl;
        tmp.start = tmp.end+1;
    }

    return result;
}
