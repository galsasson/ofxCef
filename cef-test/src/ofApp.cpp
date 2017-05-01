
#include "ofApp.h"
#include "ofAppGLFWWindow.h"

//--------------------------------------------------------------
void mouseScroll(GLFWwindow* window, double x, double y){
    ((ofApp *)ofGetAppPtr())->cefgui->mouseWheel(x*10, y*10);
}

//--------------------------------------------------------------
//--------------------------------------------------------------
void ofApp::setup(){
#if defined(TARGET_OSX)
    // add scrolling callback
    glfwSetScrollCallback( ((ofAppGLFWWindow *) ofGetWindowPtr())->getGLFWWindow(), mouseScroll);
#endif
    
    // Loaded in void ofxCEF::setup() directly just to make sure this call isn't making trouble
    string path = "file://" + ofToDataPath("html/index.html", true);
    //        path = "http://haikusinteractifs.com/";
    //path = "http://mrdoob.com/#/137/voxels_liquid";
    //        path = "http://threejs.org/examples/";
    //        path = "http://www.thefamilyfarmer.com";
    
    //cefgui->load(path.c_str());
    
    ofSetVerticalSync(true);
    ofDrawBitmapMode mode;
    ofSetDrawBitmapMode(OF_BITMAPMODE_MODEL );
    ofSetFrameRate(60);
}

//--------------------------------------------------------------
void ofApp::exit(){
    cefgui->exit();
    delete cefgui;
    cefgui = NULL;
}

//--------------------------------------------------------------
void ofApp::update(){
    
    uint64_t frameCount = ofGetFrameNum();
    
    if (cefgui) {
        if (frameCount == 0) {
            cefgui->setup();
            // Register event listener
            ofAddListener(cefgui->messageFromJS, this, &ofApp::gotMessageFromJS);
            ofAddListener(cefgui->eventFromCEF, this, &ofApp::eventFromCEF);
        }
        
        cefgui->update();
    }
    
    if (frameCount == 300) {
        string command = "sendMessageToJS('This is OF talking to you! (sent on frame number 300)')";
        cefgui->executeJS((const char*) command.c_str());
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(255,0,255);
    
    if (cefgui) {
        cefgui->draw();
    }
    return;
    
    //    ofPushMatrix();
    //    ofTranslate(ofPoint(ofGetMouseX(), ofGetMouseY()));
    //    ofScale(2,2);
    //    ofDrawBitmapStringHighlight("openframeworks !! up arrow to load new url", 0,0);
    //    ofPopMatrix();
    
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    
    /*ofSetColor(255, 0, 0);
    ofDrawCircle(10, 10, 10);
    ofSetColor(ofColor::white);*/
    
}

//--------------------------------------------------------------
void ofApp::eventFromCEF(ofxCEFEventArgs& evt){
    if (evt.type == ofxCEFEventArgs::onLoadStart) {
        cout << "Receive an event from CEF > Content loading..." << endl;
    } else if (evt.type == ofxCEFEventArgs::onLoadEnd) {
        cout << "Receive an event from CEF > Content loaded with HTTP Status Code: " << evt.httpStatusCode << endl;
    }
}

//--------------------------------------------------------------
void ofApp::gotMessageFromJS(ofxCEFMessageArgs& msg){
    cout << "Got a message of type string from JS - type: " << msg.type << " - name:: " << msg.name << " - value :: " << msg.value << endl;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == OF_KEY_UP){
        string message = ofSystemTextBoxDialog("url to load");
        if (message.length() > 0){
            cefgui->load(message.c_str());
        }
    }
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
