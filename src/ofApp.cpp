#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    string file = "/Users/gene/Desktop/audiotsnetest.json";
    ofxJSONElement result;
    
    bool parsingSuccessful = result.open(file);
    for (int i=0; i<result.size(); i++) {
        string path = result[i]["path"].asString();
        float x = result[i]["x"].asFloat();
        float y = result[i]["y"].asFloat();
        AudioClip newSound;
        newSound.setup(path, x, y);
        sounds.push_back(newSound);
    }


}

//--------------------------------------------------------------
void ofApp::update(){
    for (int i=0; i<sounds.size(); i++) {
        sounds[i].update();
    }
    ofSoundUpdate();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackgroundGradient(ofColor(100), ofColor(20));
    for (int i=0; i<sounds.size(); i++) {
        sounds[i].draw();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

    for (int i=0; i<sounds.size(); i++) {
        sounds[i].mouseMoved(x, y);
    }
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
