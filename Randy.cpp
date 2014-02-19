#include "RandomHelper.h"


float RandomHelper::randf(float min, float max){
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = max - min;
    float r = random * diff;
    return min + r;
}

float RandomHelper::randi(int min, int max){
    return ( rand() % (max - min) ) + min;
}