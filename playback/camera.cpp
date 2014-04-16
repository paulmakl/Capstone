#include "camera.h"

void camera::init(float ex, float ey, float ez, float tx, float ty, float tz, float ux, float uy, float uz){
    eyeX = ex;
    eyeY = ey;
    eyeZ = ez;
    
    targetX = tx;
    targetY = ty;
    targetZ = tz;
    
    upX = ux;
    upY = uy;
    upZ = uz;
}