#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    if(ofIsGLProgrammableRenderer()){
        topo.load("shadersGL3/topo");
	}
    
    topoImg.allocate(80, 60, OF_IMAGE_GRAYSCALE);
    topoRes = topoImg.getHeight() * topoImg.getWidth();
    
    for (int i = 0; i < topoImg.getWidth() * 2; i++) {
        float col = ofRandom(0,1);
        for (int j = 0; j < topoImg.getHeight(); j++) {
            //heights.push_back(ofMap(i, 0, topoImg.getWidth(), 1, 0,true));
            //heights.push_back(col);
            //heights.push_back(0);
            heights.push_back(ofRandom(0,1));
        }
    }
    
    landscape.set(800, 600, 80, 60);
    landscape.mapTexCoordsFromTexture(topoImg.getTextureReference());
    
    unsigned char * pixels = topoImg.getPixels();
    for (int i = 0; i < topoRes; i++) {
        pixels[i] = 0;
    }
    topoImg.update();
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    //float offSet = ofMap(ofGetMouseX(), 0, ofGetWidth(), 0, topoImg.getWidth(),true) * topoImg.getHeight();
    //float offSet = 0;
    float offSet = ofGetMouseX() * topoImg.getHeight();
    if (offSet < 0) {
        offSet = 0;
    } else if (offSet > heights.size()-topoRes){
        offSet = heights.size()-topoRes;
    }
    //cout << offSet/topoImg.getWidth() << endl;
    //cout << heights.size() << endl;
    
    unsigned char * pixels = topoImg.getPixels();
    for (int column = 0; column < topoImg.getWidth(); column++) {
        int w = topoImg.getWidth();
        int h = topoImg.getHeight();
        for(int y=0; y<h; y++) {
            int i = w * y + column;
            pixels[i] = 255 * heights[(column*h)+y+offSet];
        }
        topoImg.update();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    
    topoImg.getTextureReference().bind();
    
    topo.begin();
    
    ofPushMatrix();
    
    // translate plane into center screen.
    float tx = ofGetWidth() / 2;
    float ty = ofGetHeight() / 2;
    ofTranslate(tx, ty);
    
    // the mouse/touch Y position changes the rotation of the plane.
    //float percentY = 0.5;
    float percentY = mouseY / (float)ofGetHeight();
    float rotation = ofMap(percentY, 0, 1, -60, 60, true) + 60;
    ofRotate(rotation, 1, 0, 0);
    
    landscape.drawWireframe();
    
    ofPopMatrix();
    
    topo.end();
    
    ofSetColor(ofColor::white);
    //topoImg.draw(0, 0,800,600);
    topoImg.draw(0, 0);
    
    if (ofGetFrameNum()%3 == 0) {
        float col = ofRandom(0,1);
        for (int j = 0; j < topoImg.getHeight(); j++) {
            //heights.push_back(ofMap(i, 0, topoImg.getWidth(), 1, 0,true));
            //heights.push_back(col);
            heights.push_back(ofRandom(0,1));
        }
    }
    
    
    ofSetWindowTitle(ofToString(ofGetFrameRate(),2));
    ofDrawBitmapStringHighlight(ofToString(heights.size()), 20, ofGetHeight()-20);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
