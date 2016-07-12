#pragma once

#include "ofMain.h"
#include "ofxJSON.h"

class AudioClip {
public:
    void setup(string path, float x, float y) {
        sound.load(path);
        point.set(x, y);
        t = 0;
    }
    void update() {
        if (sound.isPlaying() && sound.getPositionMS() > 1000) {
            sound.stop();
        }
    }
    void draw() {
        if (sound.isPlaying()) {
            ofSetColor(0, 255, 0, 180);
        }
        else {
            ofSetColor(255, 180);
        }
        ofDrawCircle(ofGetWidth() * point.x, ofGetHeight() * point.y, 4);
    }
    void trigger() {
        sound.play();
        t = ofGetElapsedTimef();
    }
    void mouseMoved(int x, int y) {
        float distanceToMouse = ofDistSquared(x, y, ofGetWidth() * point.x, ofGetHeight() * point.y);
        if (distanceToMouse < 250 && !sound.isPlaying() && (ofGetElapsedTimef() - t > 2.0)) {
            trigger();
        }
    }
    ofSoundPlayer sound;
    ofPoint point;
    float t;
};

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

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
    
    vector<AudioClip> sounds;
    
};
