#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(30);
	ofBackground(255);
	ofSetWindowTitle("Insta");

	ofSetColor(0);

	this->cap.open(1);

	this->frame_img.allocate(this->cap.get(CV_CAP_PROP_FRAME_WIDTH) * 0.25, this->cap.get(CV_CAP_PROP_FRAME_HEIGHT) * 0.25, OF_IMAGE_COLOR);
	this->frame = cv::Mat(this->frame_img.getHeight(), this->frame_img.getWidth(), CV_MAKETYPE(CV_8UC3, this->frame_img.getPixels().getNumChannels()), this->frame_img.getPixels().getData(), 0);

	this->gray_img.allocate(this->cap.get(CV_CAP_PROP_FRAME_WIDTH) * 0.25, this->cap.get(CV_CAP_PROP_FRAME_HEIGHT) * 0.25, OF_IMAGE_GRAYSCALE);
	this->gray_frame = cv::Mat(this->gray_img.getHeight(), this->gray_img.getWidth(), CV_MAKETYPE(CV_8UC1, this->gray_img.getPixels().getNumChannels()), this->gray_img.getPixels().getData(), 0);

	cout << this->cap.get(CV_CAP_PROP_FRAME_WIDTH) << " : " << this->cap.get(CV_CAP_PROP_FRAME_HEIGHT) << endl;
}

//--------------------------------------------------------------
void ofApp::update() {
	if (!this->cap.isOpened()) { return; }

	cv::Mat src;
	this->cap >> src;
	if (src.empty()) { return; }
	cv::resize(src, this->frame, cv::Size(), 0.25, 0.25);

	cv::cvtColor(this->frame, this->frame, CV_RGB2BGR);
	cv::flip(this->frame, this->frame, 1);
	cv::cvtColor(this->frame, this->gray_frame, CV_RGB2GRAY);
}

//--------------------------------------------------------------
void ofApp::draw() {
	this->cam.begin();
	
	ofTranslate(-this->frame_img.getWidth() / 2, -this->frame_img.getHeight() / 2);
	
	char moji[26] = { 'A', 'B', 'C', 'D', 'E', 'F','G', 'H', 'I', 'J', 'K', 'L','M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T','U', 'V', 'W', 'X', 'Y', 'Z' };
	int value;
	for (int y = 0; y < this->gray_frame.rows; y += 4) {
		for (int x = 0; x < this->gray_frame.cols; x += 4) {
			value = this->gray_frame.at<unsigned char>(y, x);
			if (value < 64) {
				ofPushMatrix();
				ofTranslate(0, 0, -value);
				ofDrawBitmapString(moji[value / 10], x, this->gray_img.getHeight() - y);
				ofPopMatrix();
			}
		}
	}

	if (ofGetKeyPressed()) {
		this->gray_img.update();
		this->gray_img.draw(0, 0);
	}

	this->cam.end();
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
