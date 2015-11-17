#pragma once

#include "ofMain.h"


class Particle {
public:
    Particle();//Class constructor
    void setup();    //Start particle
    void update( float dt );    //Recalculate physics
    void draw();    //Draw particle
    
    ofPoint pos;    //Position
    ofPoint vel;    //Velocity
    float time;    //Time of living
    float lifetime;    //Allowed lifetime
    bool live;    //Is particle live
    bool follow; //Is the particle following another
    
    //text
    string randWord;
    string randSentence;
    float wordLen;
    float wordHeight;
    ofTrueTypeFont font;
    
};
//Control parameters class
class Params {
public:
    void setup();
    ofPoint eCenter;//Emitter center
    float eRad; //Emitter radius
    float velRad; //Initial velocity limit
    float lifetime; //Lifetime in seconds
    float rotate; //Direction rotation speed in angles per second
};
extern Params param;  //Declaration of a global variable

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    
    void keyPressed(int key);
    void keyReleased(int key);
    void windowResized(int w, int h);
    
    vector<Particle> p;	  //Particles
    float history;//Control parameter for trails
    float time0;//Time value for computing dt
    
    float bornRate;       //Particles born rate per second
    float bornCount;      //Integrated number of particles to born
    float rand;
    bool movement;
    
    
    
};
