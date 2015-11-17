#include "ofApp.h"

Params param;        //Definition of global variable


//--------------------------------------------------------------
//----------------------  Params  ------------------------------
//--------------------------------------------------------------
void Params::setup() {
    eCenter = ofPoint( ofGetWidth() / 2, ofGetHeight() / 2 );
    eRad = 50;
    velRad = 200;
    lifetime = 5.0;
    rotate = 0;
}
//--------------------------------------------------------------
//----------------------  Particle  ----------------------------
//--------------------------------------------------------------
Particle::Particle() {
    live = false;
}
//--------------------------------------------------------------

ofPoint randomPointInScreen( float maxRad ){
    ofPoint pnt;
    float rad = ofRandom( 0, maxRad );
    float angle = ofRandom( 0, M_TWO_PI );
    pnt.x = cos( angle ) * rad;
    pnt.y = sin( angle ) * rad;
    return pnt;
}
//--------------------------------------------------------------
void Particle::setup() {
    param.eCenter = ofPoint( ofRandom(ofGetWidth()), ofRandom(ofGetHeight())  );
    font.loadFont("frabk.ttf", 24);
    pos = param.eCenter + randomPointInScreen( param.eRad );
    //pos.x = ofGetWidth()-(wordLen/2);
    pos.y = ofGetHeight()/2;
    vel = randomPointInScreen( param.velRad );
    time = 0;
    lifetime = param.lifetime;
    live = true;
    follow = false;
    
    //load the text file and all all the words to a vector string
    vector<string> list;
    
    string word;
    ifstream wordfile("/Users/mtvogel/Documents/of_v0.8.4_osx_release/apps/myACIApps/Assignment_4_Code_Poetry/bin/data/textfile.txt");
    while (wordfile >> word) {
        list.push_back(word);
        
    }
    if (!wordfile.eof()) {
        cerr << "Hey there! Something went wrong when reading the list of words!\n";
        return 1;
    }
    
    //pick a random element in the word list vector
    int sentenceLen = ofRandom(2, 10);
    for (int i = 0; i<sentenceLen; i++) {
        int randElement = ofRandom(list.size());
        randWord =list.at( ofRandom(list.size()) );
        randSentence = randSentence.append(randWord);
        randSentence = randSentence.append(" ");
    }
        wordLen = randSentence.length()*16;
        wordHeight = -17;
    cerr << wordLen<<endl;
    
    //set color of text
    //ofSetColor( ofRandom(255), ofRandom(255), ofRandom(255) );
    
}
//--------------------------------------------------------------
void Particle::update( float dt ){
    
    if ( live ) {
        //Rotate vel
        vel.rotate( 0, 0, param.rotate * dt );
        
        //Update pos
        pos.x = (ofGetWidth()/2)-(wordLen/2);


        
        
        //Update time
        time += dt;
        
        //Delete offscreen particles
        int right = ofGetWidth();
        int bottom = ofGetHeight();
        
        if (pos.x > right or pos.x < 0){
            live = false;
        }
        if (pos.y > bottom or pos.y < 0){
            live = false;
        }
        //check if particle should die
        if ( time >= lifetime ) {
            live = false;   //Particle is now considered as died
        }
        
        
    }
}
//--------------------------------------------------------------

void Particle::draw(){
    if ( live ) {
        font.drawString(randSentence, pos.x, pos.y);
        //ofRect(pos.x, pos.y, wordLen, wordHeight);
        
    }
}

//--------------------------------------------------------------
//----------------------  App  ---------------------------------
//--------------------------------------------------------------

void ofApp::setup(){
    ofSetFrameRate( 30 );    //Set screen frame rate
    
    //set up sound
    ofSetVerticalSync(true);
    
    
    //Allocate drawing buffer
    int w = ofGetWidth();
    int h = ofGetHeight();
    
    //Fill buffer with white color
    ofBackground(ofColor::black);
    ofEnableSmoothing();
    
    //Set up parameters
    param.setup();          //Global parameters
    history = 0.995;
    bornRate = 1;
    
    bornCount = 0;
    time0 = ofGetElapsedTimef();
    
    movement = true;
    
    //create first particle
    Particle newP;
    newP.setup();            //Start a new particle
    p.push_back( newP );     //Add this particle to array
}
//--------------------------------------------------------------

void ofApp::update(){
    //Compute dt
    float time = ofGetElapsedTimef();
    float dt = ofClamp( time - time0, 0, 0.1 );
    time0 = time;
    
    //delete particles if they're dead
    int i=0;
    while (i < p.size()) {
        if ( !p[i].live ) {
            p.erase( p.begin() + i );
                    }
        else {
            i++;
        }
    }
    cerr << p[0].time <<endl;
    if ( p[0].time >= p[0].lifetime ) {
        Particle newP;
        newP.setup();            //Start a new particle
        p.push_back( newP );     //Add this particle to array
    }
    //make new particles


    
    //Update the particle
    for (int i = 0; i<p.size(); i++)
    {
            p[i].update( dt );
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground( 0, 0, 0 );  //Set white background
    
    //Draw the particle
    ofFill();
    for (int i=0; i<p.size(); i++) {
        p[i].draw();
    }
    
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'f') {
        ofToggleFullscreen();
    }
    if (key == ' ') {
        
        //delete particles if they're dead
        for (int i=0; i<p.size(); i++) {
            cerr << "erase" << endl;
            p.erase(p.begin() , p.end() );
        }
        Particle newP;
        newP.setup();            //Start a new particle
        p.push_back( newP );     //Add this particle to array
    }
    if (key == OF_KEY_RETURN) {
        if (movement == true) {
            movement = false;
        }
        else {
            movement = true;
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

