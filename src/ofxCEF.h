#include "cef_app.h"

#include "ofxCEFBrowserClient.h"
#include "ofxCEFRenderHandler.h"

#ifndef CEFGUI_H
#define CEFGUI_H

//--------------------------------------------------------------
class ofxCEFMessageArgs : public ofEventArgs{
public:
    string name;
    string type;
    string value;
};

//--------------------------------------------------------------
class ofxCEFEventArgs : public ofEventArgs{
public:
    enum Type{
        onLoadStart,
        onLoadEnd
    } type;
    int httpStatusCode;
};

//--------------------------------------------------------------
class ofxCEF;

void initofxCEF(int argc, char** argv);
void updateCEF();

//--------------------------------------------------------------
class ofxCEF
{
public:
    ofxCEF();
    ~ofxCEF();
    
    ofxCEF(const ofxCEF& other) = delete;
    ofxCEF & operator=(const ofxCEF&) = delete;
    
	void exit();

    void load(const char*);
    void draw(void);
    void reshape(int, int);
    
    void setup(const string& url = "", int width = 0, int height = 0);
    
    void mouseWheel(int, int);
    
    void mousePressed(ofMouseEventArgs &e);
    void mouseReleased(ofMouseEventArgs &e);
    void mouseMoved(ofMouseEventArgs &e);
    void mouseDragged(ofMouseEventArgs &e);
    
    void keyPressed(ofKeyEventArgs &e);
    void keyReleased(ofKeyEventArgs &e);
    
    void windowResized(ofResizeEventArgs &e);
    
    void enableEvents();
    void disableEvents();
    
    void enableResize();
    void disableResize();
    
    void executeJS(const char*);

    void notificationHandler();
    
    void onLoadStart();
    void onLoadEnd(int httpStatusCode);
    
    void gotMessageFromJS(string name, string type, string value);

    ofEvent<ofxCEFMessageArgs> messageFromJS;
    ofEvent<ofxCEFEventArgs> eventFromCEF;

 // private:
    int mouseX, mouseY;

    CefRefPtr<CefBrowser> browser;
    CefRefPtr<ofxCEFBrowserClient> client;

    ofxCEFRenderHandler* renderHandler;
    
    bool fixedSize;
    float width_, height_;

    uint64_t browerCreation;
};

typedef void (ofxCEF::*notificationHandler)();

#endif
