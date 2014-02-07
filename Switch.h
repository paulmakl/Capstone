#ifndef SWITCH_H_
#define SWITCH_H_

#include "Physics.h"
#include "Draw.h"

#define pixels 720

class Switch{
public:
	Environment env;
    Physics phys;
    static Draw draw;
    

    void init(int argc, char **argv);
    void timer(int id);
    void display();

#endif
