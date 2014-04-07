#ifndef READER_H_
#define READER_H_

#include <fstream>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <algorithm>
#include <string>
#include <vector>
#include "video.h"
#include <ctype.h>

using namespace std;

class reader{
public:
    std::string path;
    std::fstream myfile;
    reader(string path);
    video vid;
    void read();
    void setVideoSize();
    void setVideoState(int i);
    
    
    bool is_number(string s);
    string lowercase(string str);
    /*
     * Takes a string, and separates values into
     * slots in the array
     */
    vector<string> chop(string line);
    
};

#endif
