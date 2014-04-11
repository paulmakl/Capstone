#ifndef CAMERA_H_
#define CAMERA_H_

class camera{
public:
    float eyeX;
    float eyeY;
    float eyeZ;
    
    float targetX;
    float targetY;
    float targetZ;
    
    float upX;
    float upY;
    float upZ;
    
    float distance;
    
    float angle;
    
    void init(float ex, float ey, float ez, float tx, float ty, float tz, float ux, float uy, float uz);
    
    
    //gluPerspective(85.0, 1.0, 0.001, x.vid.size.x);
	//float eyeX, eyeY, eyeZ, targetX, targetY, targetZ, upX, upY, upZ;
    //float distance = x.vid.size.x;
    //float angle = 0.0f;
    /*eyeX = distance;//*cos(angle);
    eyeY = 3.0f;//env.ySize/1.3f;
    eyeZ = distance;//*sin(angle);
    targetX = x.vid.size.x/2.0f;
    targetY = x.vid.size.y/2.0f;
    targetZ = x.vid.size.z/2.0f;
    upX = 0.0f;
    upY = 1.0f;
    upZ = 0.0f;
    
    gluLookAt(eyeX, eyeY, eyeZ, targetX, targetY, targetZ, upX, upY, upZ);*/
    
    
    
};
#endif