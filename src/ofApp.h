#pragma once

#include "ofMain.h"
#include "ofxSimpleScreenRecorder.h"



class ofApp : public ofBaseApp {
    
public:
		
    void setup();
    void update();
    void draw();
    void exit();

    void keyPressed(int key);
    void mouseReleased(int x, int y, int button);
    void renderInfoGraphics();

    
private:
    ofxSimpleScreenRecorder mRenderer;
    ofAVFoundationPlayer myMovie;
    bool osd_on;
    bool startInfoGraphics;
    float* current_xs;
    float* current_ys;
    int currentIndex;
    float shapeBaseY;

};
