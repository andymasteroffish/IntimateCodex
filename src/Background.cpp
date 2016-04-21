//
//  Background.cpp
//  emptyExample
//
//  Created by Andy Wallace on 9/25/15.
//
//

#include "Background.h"


void Background::setup(){
    for (int i=0; i<80; i++){
        ofVec2f point(ofRandom(ofGetWidth()), ofRandom(ofGetHeight()));
        points.push_back(point);
    }
}

void Background::update(){
    for (int i=0; i<points.size(); i++){
        points[i].y += ofRandom(-1,3);
        
        if (points[i].y > ofGetHeight()){
            points[i].x = ofRandom(ofGetWidth());
            points[i].y = -5;
        }
    }
}

void Background::draw(){
    ofSetColor(255);
    for (int i=0; i<points.size(); i++){
        ofRect(points[i].x, points[i].y, 1,1);
    }
}