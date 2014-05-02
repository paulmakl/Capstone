#ifndef COG_H_
#define COG_H_
#include <vector>
#include "particle.h"
#include "vectors.h"
using namespace std;
class Particle;

class COG
{
public:
    vector <Particle*> particles;
    Vec3 center;
    Vec3 rotationVector;
    Vec3 translationVector;
    int numParticles;
    
    void init();

    void rotateCOG(Vec3 rotation);
    void translateCOG(Vec3 translation);

    void updateCenter();
    void addParticle(Particle* p);

    int getSize();
    double getMass();
};

#endif
