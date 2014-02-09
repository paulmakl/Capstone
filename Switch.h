#ifndef SWITCH_H_
#define SWITCH_H_

#include "Physics.h"
#include "Draw.h"

#ifdef __APPLE__
#define pixels 720
#else
#define pixels 900
#endif

class Switch{
public:
//	Environment env;
//    Physics phys;
//    Draw draw;
    
    static void init(int argc, char **argv);
};
#endif
