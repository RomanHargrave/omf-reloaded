#include <cstdlib>
#include <iostream>
#include <omfsounds.h>

using namespace std;

int main(int argc, char ** argv)
{

    string str;
    ifstream in;
    ofstream ou;

    // Info:
    cout << "Sounds extractor. Write the filepath of the SOUNDS.DAT (it doesn't need to be named like that)." << endl;
    getline(cin,str);

    // File open:
    in.open(str.c_str());
    if (in.bad())
    {
        cout << "The file \"" << str << "\" could not be opened." << endl;
        exit(0);
    }

    cout << "Write the filepath where you want to rip the SOUNDS.DAT." << endl;
    getline(cin,str);

    ou.open(str.c_str());
    if (ou.bad())
    {
        cout << "The file \"" << str << "\" could not be opened." << endl;
        exit(0);
    }

    vector<sound_header> s_info = getAllSoundsInfo(in);

    cout << "Write the sound you want to rip. If you want a continuous full sound (all sounds in one) write \"all\"" << endl;
    cin >> str;

    if (str == "all")
    {
        DWORD start = s_info[0].start;
        DWORD end = s_info[s_info.size()-1].end;
        in.seekg(start,ifstream::beg);
        char g;
        while (end > start)
        {
            g = in.get();
            ou.put(g);
            end--;
        }
    }
    else
    {
        int m = atoi(str.c_str());
        if (m > s_info.size())
        {
            cout << "The number you wrote is too big." << endl;
            exit(0);
        }
        if (m < 1)
        {
            cout << "The number you wrote is too small." << endl;
        }
        m--;
        DWORD start = s_info[m].start;
        DWORD end = s_info[m].end;
        in.seekg(start,ifstream::beg);
        char g;
        while (end > start)
        {
            g = in.get();
            ou.put(g);
            end--;
        }
    }

    return 0;
}
