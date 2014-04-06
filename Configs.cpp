#include "Configs.h"

/*
 * Node Configs
 */

Node Configs::random_config_nodes(int x, int y, int z){
    Node a;
    
    float r = 0.2f + rand()%30/100.0f;
    float g = 0.2f + rand()%30/100.0f;
    float b = 0.2f + rand()%30/100.0f;
    a.setRGBA(r, g, b, 1.0f);
    a.setForce(0.0 + rand()%100/1000.0f - 0.055f, 0.0 + rand()%100/1000.0f - 0.055f, 0);
    return a;
}

Node Configs::towards_center_nodes(int x, int y, int ySize){
    Node a;
    if (y > ySize/2) {
        a.setRGBA(1.0f, 1.0f, 0.0f, 1.0f);
        a.setForce(0, -0.03, 0);
    }else{
        a.setRGBA(0.0f, 1.0f, 1.0f, 1.0f);
        a.setForce(0, 0.03, 0);
    }
    
    return a;
}

Node Configs::towards_center_2_nodes(int x, int y, int ySize){
    Node a;
    float force = y * 0.01;
    if (y > ySize/2) {
        a.setRGBA(1.0f, 1.0f, 0.0f, 1.0f);
        a.setForce(0, -1 * force, 0);
    }else{
        a.setRGBA(0.0f, 1.0f, 1.0f, 1.0f);
        a.setForce(0, force, 0);
    }
    
    return a;
}

Node Configs::up_nodes(int x, int y){
    Node a;
    a.setRGBA(0.4f, 0.4f, 0.2f, 1.0f);
    a.setForce(0.0f, 1.0f, 0.0f);
    return a;
}

Node Configs::dead_config_nodes()
{
    Node a;
    a.setRGBA(0.1f, 0.1f, 0.1f, 1.0f);
    a.setForce(0.0f, 0.0f, 0.0f);
    return a;
}

/*
 * Particles
 */
Particle Configs::random_confic_particles(int xSize, int ySize, int zSize)
{
    Particle a;
    float xPos = Randy::randf(2, xSize/5.0f) + xSize/4.0f;
    float yPos = Randy::randf(2, ySize-1) ;
    float zPos = Randy::randf(2, zSize/5.0f) + xSize/4.0f;
    a.setPosition(xPos, yPos, zPos);
    
    float xVelo = Randy::randf(-0.03, 0.03);
    float yVelo = Randy::randf(-0.3, -0.4);
    float zVelo = Randy::randf(-0.03, 0.03);
    a.setVelocity(xVelo, yVelo, zVelo);

    a.setColor(0.1f, 1.0f, 1.0f);
    a.setMass(Randy::randf(0.0f, 0.0f)); // 1 = maximum inertia, 0 = no intertia
    a.setVolume(Randy::randf(0.02f, 0.2f));
    return a;
}

/*Particle Configs::up_config_particles(int xSize, int ySize){
    Particle a;
    float xPos = 0.1f;
    float yPos = 0.1f;
    
    a.setPosition(xPos, yPos);
    a.setVelocity(0.2f, 0.0f);
    a.setColor(0.1f, 1.0f, 1.0f);
    return a;
}

Particle Configs::up_config_2_particles(int xSize, int ySize){
    Particle a;
    float xPos = Randy::randf(0, xSize/2.0f) + xSize/4.0f;
    float yPos = Randy::randf(0, xSize/2.0f) + xSize/4.0f;
    
    float xVelo = Randy::randf(-2, 2);
    float yVelo = Randy::randf(-0.1, 0.6);
    
    a.setPosition(xPos, yPos);
    a.setVelocity(xVelo, yVelo);
    a.setColor(0.1f, 1.0f, 1.0f);
    return a;
}

Particle Configs::test_config_particles(){
    Particle a;
    float xPos = 0;
    float yPos = 0;
    
    a.setPosition(xPos, yPos);
    a.setVelocity(0.2f, 0.2f);
    a.setColor(0.1f, 1.0f, 1.0f);
    return a;
}*/


























