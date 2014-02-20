#include "Randy.h"


float Randy::randf(float min, float max){
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = max - min;
    float r = random * diff;
    return min + r;
}

float Randy::randi(int min, int max){
    return ( rand() % (max - min) ) + min;
}

void Randy::seed(){
    unsigned long x = time(NULL);
    rand();
    rand();
    srand(x);
}