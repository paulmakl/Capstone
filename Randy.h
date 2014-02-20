#ifndef RANDY_H_
#define RANDY_H_

#include <math.h>
#include <cstdlib>
#include <time.h>
#include <iostream>

/*
 * Helper Methods for calculating random numbers between two values
 */

class Randy{
public:
    static float randf(float min, float max);
    static float randi(int min, int max);
    static void seed();
    
};

#endif