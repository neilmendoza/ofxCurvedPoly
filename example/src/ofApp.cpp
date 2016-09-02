#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    ofBackground(0);
    ofNoFill();
    ofSetLineWidth(4.f);
    const ofVec2f center(.5f * ofGetWidth(), .5f * ofGetHeight());
    const float radius = 200.f;
    const unsigned numPoints = 10;
    for (unsigned i = 0; i < numPoints; ++i)
    {
        curvedPoly.push_back(center.x + radius * sin(TWO_PI * (float)i / numPoints),
                             center.y + radius * cos(TWO_PI * (float)i / numPoints));
    }
    curvedPoly.createBeziers();
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw()
{
    ofSetColor(0, 0, 255);
    ofBeginShape();
    for (unsigned i = 0; i < curvedPoly.size(); ++i)
    {
        ofVertex(curvedPoly[i].x, curvedPoly[i].y);
    }
    ofEndShape();
    
    ofSetColor(0, 255, 255);
    ofBeginShape();
    const unsigned numSamples = 100;
    for (unsigned i = 0; i <= numSamples; ++i)
    {
        ofVec2f v = curvedPoly.sampleAt((i % numSamples) / (float)numSamples);
        ofVertex(v.x, v.y);
    }
    ofEndShape();
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
