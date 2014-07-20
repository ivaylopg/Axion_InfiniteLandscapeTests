#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    if(ofIsGLProgrammableRenderer()){
		fxaa.load("shadersGL3/fxaa");
        //fxaa.load("shadersGL3/topo");
	}
    
    ofFbo::Settings settings;
    settings.numSamples = 0; // also try 8, if your GPU supports it
    settings.useDepth = true;
    settings.width = ofGetWidth();
    settings.height = ofGetHeight();
    
    myFbo.allocate(settings);
    myAAFbo.allocate(settings);
    
    topoImg.allocate(80, 60, OF_IMAGE_GRAYSCALE);
    
    landscape.set(800, 600, 80, 60);
    landscape.mapTexCoordsFromTexture(topoImg.getTextureReference());
    column = 1;
    unsigned char * pixels = topoImg.getPixels();
    int topoRes = topoImg.getWidth() * topoImg.getHeight();
    for (int i = 0; i < topoRes; i++) {
        pixels[i] = 0;
    }
    topoImg.update();
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    /*
    myFbo.begin();                              // FXAA tests
    ofSetColor(ofColor::white);
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2,ofGetHeight()/2);
    ofSpherePrimitive(100.f, 3).getMesh().drawWireframe();
    ofPopMatrix();
    myFbo.end();

    myAAFbo.begin();
    fxaa.begin();
    myFbo.draw(ofVec2f(0,0));
    fxaa.end();
    myAAFbo.end();
    */
    
    
    if (column <= topoImg.getWidth()) {
        unsigned char * pixels = topoImg.getPixels();
        int w = topoImg.getWidth();
        int h = topoImg.getHeight();
        for(int y=0; y<h; y++) {
            int i = y * w + column;
            float topoHeight = ofRandom(0,1);
            pixels[i] = 255 * topoHeight;
        }
        topoImg.update();
    }
    
    
    
    if (column <= topoImg.getWidth()) {
        column++;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    /*
    myFbo.draw(ofVec2f(0-ofGetWidth()/3,0));    // FXAA tests
    myAAFbo.draw(ofVec2f(0+ofGetWidth()/3,0));
    */
    
    topoImg.draw(0, 0,800,600);
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
