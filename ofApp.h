/************************************************************
************************************************************/
#pragma once

/************************************************************
************************************************************/
#include "ofMain.h"
#include "ofxOsc.h"

#include "ofxOsc_BiDirection.h"
#include "ofxSyphon.h"
#include "ofxGui.h"

#include "sjCommon.h"

/************************************************************
************************************************************/
class ofApp : public ofBaseApp{
private:
	/****************************************
	****************************************/
	enum{
	/*
		WIDTH = 1280,
		HEIGHT = 720,
	*/
		WIDTH = 640,
		HEIGHT = 360,
	};
	
	/****************************************
	****************************************/
	/********************
	********************/
	OSC_TARGET Osc;
	ofxSyphonServer SyphonTexture;
	ofFbo fbo;
	
	ofVideoGrabber *VideoCam;
	int Cam_id;
	
	bool b_Enable;
	
	/********************
	********************/
	ofxPanel gui;
	ofxColorSlider guiColor;
	
public:
	/****************************************
	****************************************/
	void setup();
	void update();
	void draw();
	
	ofApp(int _id);
	~ofApp();
	void exit();
	void setup_gui();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
	
};
