#include "ofApp.h"

//Arrays with the coordinates of the info graphics
float xs[] = {0, 72,180,265, 360,480 ,596};
float ys[] = {336,70,120,45,190,25 ,336};

//min diff to stop the animation
const float min_diff = 2.0;

//speed of the animation
const float speed = 0.15;

const string video_path = "movie.mp4";

//--------------------------------------------------------------
void ofApp::setup() {
    
    //Initialize graphics
    ofBackground(0);
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    ofEnableSmoothing();
    ofHideCursor();
    ofNoFill();
    ofSetLineWidth(4);
    mRenderer.setup(ofGetWidth(), ofGetHeight());
    
    //Initialize variables
    startInfoGraphics = false;
    current_xs = NULL;
    current_ys = NULL;
    osd_on = false;
    currentIndex = 0;
    
    shapeBaseY = 0;
    
    current_xs = new float[(sizeof(xs)/sizeof(*xs))];
    current_ys = new float[(sizeof(ys)/sizeof(*ys))];
    current_xs[0] = xs[0];
    current_ys[0] = ys[0];
    
    int min = INT_MIN;
    for (int i = 0; i < ((sizeof(xs)/sizeof(*xs))-1); ++i) {
        if( ys[i] < min ){
            min = ys[i];
        }
    }
    shapeBaseY = min;

    //Load movie
    myMovie.load(video_path);
    myMovie.setLoopState(OF_LOOP_NORMAL);
    myMovie.play();

    
}


//--------------------------------------------------------------
void ofApp::update()
{
    myMovie.update();
    
    
    if(startInfoGraphics){
        
    //Iterate through the info graphic coords
    if (currentIndex < ((sizeof(xs)/sizeof(*xs))-1) ) {
        
       // OfPrint("currentIndex="+currentIndex);
        float diffX = abs(current_xs[currentIndex] - xs[currentIndex+1]);
        
        if ( diffX > min_diff) {
            current_xs[currentIndex] = current_xs[currentIndex] + (xs[currentIndex+1] - current_xs[currentIndex])*speed;
            current_ys[currentIndex] = current_ys[currentIndex] + (ys[currentIndex+1] - current_ys[currentIndex])*speed;
        } else {
            //we reach final position
            current_xs[currentIndex] = xs[currentIndex+1];
            current_ys[currentIndex] = ys[currentIndex+1];
            
            currentIndex++;
            if (currentIndex < (sizeof(xs)/sizeof(*xs))-1) {
                current_xs[currentIndex] = xs[currentIndex];
                current_ys[currentIndex]   = ys[currentIndex];
            }
        }
        
    }
    }

}

void ofApp::renderInfoGraphics(){
ofSetHexColor(0xFF5289);
ofNoFill();

for (int i = 0; i < ((sizeof(xs)/sizeof(*xs))-1); ++i) {
    if ( i <= currentIndex) {
        ofDrawLine(xs[i], ys[i],current_xs[i], current_ys[i]);
        ofVertex(xs[i], ys[i]);
    }
}

//Shape
ofFill();
ofSetColor(255,82,137,30);
ofBeginShape();
ofVertex(xs[0], ys[0]);

for (int i = 0; i < ((sizeof(xs)/sizeof(*xs))-1); ++i) {
    if ( i <= currentIndex) {
        ofDrawLine(xs[i], ys[i],current_xs[i], current_ys[i]);
        ofVertex(current_xs[i], current_ys[i]);
    }
}
ofVertex(current_xs[currentIndex], ys[0]);

ofEndShape();

}

//--------------------------------------------------------------
void ofApp::draw() {
    
    mRenderer.begin();
    ofBackground(0);
    ofSetColor(255);
 
    myMovie.draw(0, 0);
    
    if(startInfoGraphics){
        renderInfoGraphics();
    }
    mRenderer.end();


}

void ofApp::exit() {
 
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    
    //Start recording frames
    if(key == '1')
        mRenderer.start();
    //Stop recording frames
    else if(key == '2')
        mRenderer.stop();
 
    
}

void ofApp::mouseReleased(int x, int y, int button) {
    
    //Start info graphics
    startInfoGraphics = true;
    
}
