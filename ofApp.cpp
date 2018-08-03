/************************************************************
************************************************************/
#include "ofApp.h"


/************************************************************
************************************************************/
/******************************
******************************/
ofApp::ofApp(int _id)
: Osc("127.0.0.1", 12353, 12354)
, Cam_id(_id)
, VideoCam(NULL)
, b_Enable(false)
{
}

/******************************
******************************/
ofApp::~ofApp()
{
	if(VideoCam) delete VideoCam;
}

/******************************
******************************/
void ofApp::exit()
{
	printMessage("Good-bye");
}

//--------------------------------------------------------------
void ofApp::setup(){
	/********************
	********************/
	ofSetWindowTitle("Kinobi:LiveCam");
	ofSetVerticalSync(true);
	ofSetFrameRate(30); // if vertical sync is off, we can go a bit fast... this caps the framerate at 60fps.
	ofSetWindowShape(WIDTH, HEIGHT);
	ofSetEscapeQuitsApp(false);
	
	ofEnableAlphaBlending();
	ofEnableBlendMode(OF_BLENDMODE_ALPHA);
	// ofEnableBlendMode(OF_BLENDMODE_ADD);
	// ofEnableSmoothing();
	
	ofSetCircleResolution(50);
	
	/********************
	********************/
	setup_gui();
	SyphonTexture.setName("LiveCam");
	
	/********************
	********************/
	VideoCam = new ofVideoGrabber;
	
	ofSetLogLevel(OF_LOG_VERBOSE);
    VideoCam->setVerbose(true);
	
	VideoCam->listDevices();// 上 2行がないと、表示されない.
	
	if(Cam_id == -1){
		std::exit(1);
	}else{
		VideoCam->setDeviceID(Cam_id);
		VideoCam->initGrabber(WIDTH, HEIGHT);
	}
}

/******************************
******************************/
void ofApp::setup_gui()
{
	/********************
	********************/
	gui.setup();
	{
		ofColor initColor = ofColor(255, 255, 255, 255);
		ofColor minColor = ofColor(0, 0, 0, 0);
		ofColor maxColor = ofColor(255, 255, 255, 255);
		
		gui.add(guiColor.setup("color", initColor, minColor, maxColor));
	}
}

//--------------------------------------------------------------
void ofApp::update(){
	/********************
	********************/
	while(Osc.OscReceive.hasWaitingMessages()){
		ofxOscMessage m_receive;
		Osc.OscReceive.getNextMessage(&m_receive);
		
		if(m_receive.getAddress() == "/Quit"){
			int dummy = m_receive.getArgAsInt32(0);
			ofExit();
			return;
			
		}else if(m_receive.getAddress() == "/PlayStop"){
			b_Enable = m_receive.getArgAsInt32(0);
		}
	}

	/********************
	********************/
	if(b_Enable){
		VideoCam->update();
		if(VideoCam->isFrameNew()){
			// nothing.
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	/********************
	********************/
	// Clear with alpha, so we can capture via syphon and composite elsewhere should we want.
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	/********************
	********************/
	ofClear(0, 0, 0, 0);
	
	/********************
	********************/
	// ofSetColor(255, 255, 255, 255);
	ofColor BaseColor = guiColor;
	ofSetColor(BaseColor);
	
	/********************
	********************/
	if(b_Enable){
		VideoCam->draw(0, 0, ofGetWidth(), ofGetHeight());
		SyphonTexture.publishScreen();
		
	}else{
		ofSetColor(255);
		
		char buf[BUF_SIZE];
		sprintf(buf, "press space or send osc to enable");
		ofDrawBitmapString(buf, 50, 50);
	}
	
	/********************
	oF wallのみの情報表示
	********************/
	gui.draw();

	/*
	ofSetColor(255, 0, 0, 255);
	
	char buf[BUF_SIZE];
	sprintf(buf, "%7.4f", video.getPosition());
	ofDrawBitmapString(buf, 100, 50);
	
	if(BootMode == BOOTMODE_PLAY){
		float MousePos = ofMap(mouseX, 0, ofGetWidth(), 0, 1);
		sprintf(buf, "%7.4f", MousePos);
		ofDrawBitmapString(buf, 100, 70);
	}
	*/
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch(key){
		case ' ':
			b_Enable = !b_Enable;
			break;
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
