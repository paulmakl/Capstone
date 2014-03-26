#include <iostream>
#include <fstream>
#include <string>

#ifdef __APPLE__
#include "/usr/local/Cellar/freeglut/2.8.1/include/GL/glut.h"
#include "/usr/local/Cellar/freeglut/2.8.1/include/GL/freeglut_ext.h"
#include "/usr/local/Cellar/freeglut/2.8.1/include/GL/freeglut_std.h"
#include "/usr/local/Cellar/freeglut/2.8.1/include/GL/freeglut.h"
#define path "/Users/paulmakl/Documents/Capstone/video.txt"
#else
#include <GL/freeglut.h>  // GLUT, includes glu.h and gl.h
#include <windows.h>
#endif

using namespace std;

int main(int argc, char** argv)
{
    fstream myfile;
    myfile.open(path);
    cout << "hello world";
    string line;
    while(getline(myfile, line)){
        std::string::iterator end_pos = std::remove(line.begin(), line.end(), ' ');
        line.erase(end_pos, line.end());
        cout << line << "\n";
    }
    myfile.close();
	return 0;
};