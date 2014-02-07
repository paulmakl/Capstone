#ifndef SWITCH_H_
#define SWITCH_H_

<<<<<<< HEAD
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
=======
#ifdef __APPLE__
#define pixels 720
#else
#define pixels 900
#endif

#define xSize 64
#define ySize 64 // For now, keep xSize and ySize the same!
#define numParticles 100000
#define numShapes 1

#include "Physics.h"
#include "Draw.h"

class Switch{
public:
    Physics phys;
    Draw draw;
    Environment env;
    
    void init();
    void loop();
>>>>>>> 7c40d12ca73902e6aa832c090e28c900f5c17c32
    
    
};

<<<<<<< HEAD
#endif
=======
#endif
>>>>>>> 7c40d12ca73902e6aa832c090e28c900f5c17c32
