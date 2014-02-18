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
    a.setRGBA(1.0f, 1.0f, 0.0f, 1.0f);
    a.setForce(0.0f, 1.0f);
    return a;
}

Node Configs::dead_config_nodes(){
    Node a;
    a.setRGBA(1.0f, 1.0f, 0.0f, 1.0f);
    a.setForce(0.0f, 0.0f);
    return a;
}

/*
 * Particles
 */
Particle Configs::random_confic_particles(int xSize, int ySize){
    Particle a;
    float xPos = (float)(rand()%(xSize*100)) / 100.0f;
    float yPos = (float)(rand()%(ySize*100)) / 100.0f;
    
    a.setPosition(xPos, yPos);
    
    float xVelo = (rand()%10)/1.0f - 0.0055f;
    float yVelo = (rand()%10)/1.0f - 0.0055f;
    a.setVelocity(xVelo, yVelo);
    a.setColor( 1.0f, 0.0f, 0.0f );
    return a;
}

Particle Configs::up_config_particles(int xSize, int ySize){
    Particle a;
    float xPos = 0.1f;
    float yPos = 0.1f;
    
    a.setPosition(xPos, yPos);
    a.setVelocity(0.0f, 0.2f);
    a.setColor(0.1f, 1.0f, 1.0f);
    return a;
}



























