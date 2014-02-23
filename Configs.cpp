#include "Configs.h"

/*
 * Node Configs
 */

Node Configs::random_config_nodes(int x, int y){
    Node a;
    
    float r = 0.2f + rand()%30/100.0f;
    float g = 0.2f + rand()%30/100.0f;
    float b = 0.2f + rand()%30/100.0f;
    a.setRGBA(r, g, b, 1.0f);
    a.setForce(0.0 + rand()%100/1000.0f - 0.055f, 0.0 + rand()%100/1000.0f - 0.055f);
    return a;
}

Node Configs::towards_center_nodes(int x, int y, int ySize){
    Node a;
    if (y > ySize/2) {
        a.setRGBA(1.0f, 1.0f, 0.0f, 1.0f);
        a.setForce(0, -0.03);
    }else{
        a.setRGBA(0.0f, 1.0f, 1.0f, 1.0f);
        a.setForce(0, 0.03);
    }
    
    return a;
}

Node Configs::towards_center_2_nodes(int x, int y, int ySize){
    Node a;
    float force = y * 0.01;
    if (y > ySize/2) {
        a.setRGBA(1.0f, 1.0f, 0.0f, 1.0f);
        a.setForce(0, -1 * force);
    }else{
        a.setRGBA(0.0f, 1.0f, 1.0f, 1.0f);
        a.setForce(0, force);
    }
    
    return a;
}

Node Configs::up_nodes(int x, int y){
    Node a;
    a.setRGBA(0.4f, 0.4f, 0.2f, 1.0f);
    a.setForce(0.0f, 1.0f);
    return a;
}

Node Configs::dead_config_nodes(){
    Node a;
    a.setRGBA(0.0f, 0.0f, 0.0f, 1.0f);
    a.setForce(0.0f, 0.0f);
    return a;
}

/*
 * Particles
 */
Particle Configs::random_confic_particles(int xSize, int ySize){
    Particle a;
    float xPos = Randy::randf(0, xSize/2) + xSize/4;
    float yPos = Randy::randf(0, xSize/2) + xSize/4;
    
    a.setPosition(xPos, yPos);
    
    float xVelo = Randy::randf(-0.3, 0.3);
    float yVelo = Randy::randf(-0.3, 0.3);

    a.setVelocity(xVelo, yVelo);
    a.setColor( 0.1f, 1.0f, 1.0f );
    return a;
}

Particle Configs::up_config_particles(int xSize, int ySize){
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
    float xPos = Randy::randf(1, xSize - 2);
    float yPos = Randy::randf(1, ySize - 2);
    
    a.setPosition(xPos, yPos);
    a.setVelocity(0.2f, 0.2f);
    a.setColor(0.1f, 1.0f, 1.0f);
    return a;
}



























