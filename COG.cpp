#include "COG.h"

void COG::updateCenter(){
    Vec3 acc;
    acc.x = 0;
    acc.y = 0;
    acc.z = 0;
    for (int i = 0; i < numParticles; i++) {
        acc.x += particles[i] -> position.x;
        acc.y += particles[i] -> position.y;
        acc.z += particles[i] -> position.z;
    }
    
    acc.x = acc.x / particles.size();
    acc.y = acc.y / particles.size();
    acc.z = acc.z / particles.size();
    center = acc;
}

void COG::addParticles(Particle *p){
    if(particles.size() <= 0)
    {
        particles.resize(100);
    }
    else if(particles[particles.size() - 1] != NULL){
        particles.resize(particles.size() * 2);
    }
    numParticles++;
    particles[numParticles-1];
    
    
}