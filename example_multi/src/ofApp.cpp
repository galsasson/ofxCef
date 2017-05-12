#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofSetDrawBitmapMode(OF_BITMAPMODE_MODEL);
    ofSetFrameRate(60);
    
    width = 100;
    height = 100;
}

//--------------------------------------------------------------
void ofApp::update(){
    // This is not called on the individual ofxCEF instances but on the main CefApp
    updateCEF();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(255,0,255);
    
    ofPushMatrix();
    for (auto& cef : cefs) {
        cef->draw();
        ofTranslate(width, 0);
    }
    ofPopMatrix();
    
    int textOffsetY = height + 20;
    
    ofDrawBitmapString("Press `n` to create new instances", 10, textOffsetY);
    ofDrawBitmapString("Press `d` to remove instances", 10, textOffsetY+20);
    ofDrawBitmapString("A white square tells you something is wrong", 10, textOffsetY+40);
    
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if (key == 'n') {
        cefs.emplace_back(new ofxCEF());
        string url = "file://" + ofToDataPath("html/index.html", true);
        /*switch (cefs.size()) {
         case 1:
         url = "http://haikusinteractifs.com/";
         break;
         case 2:
         url = "http://mrdoob.com/#/137/voxels_liquid";
         break;
         case 3:
         url = "http://threejs.org/examples/";
         break;
         case 4:
         url = "http://www.thefamilyfarmer.com";
         break;
         
         default:
         break;
         }*/
        cefs.back()->setup(url, width, height);
        //cefs.back()->disableEvents();
    }
    if (key == 'w') {
        for (auto& cef : cefs) {
            cef->reshape(width, height);
        }
    }
    if (key == 'r') {
        for (auto& cef : cefs) {
            cef->browser->Reload();
        }
    }
    if (key == 'e') {
        for (auto& cef : cefs) {
            cef->enableEvents();
        }
    }
    if (key == 'd') {
        if (cefs.size() > 0) {
            cefs.pop_back();
        }
    }
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
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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