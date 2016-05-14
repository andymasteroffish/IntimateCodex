//
//  Background.h
//  emptyExample
//
//  Created by Andy Wallace on 9/25/15.
//
//

#ifndef __emptyExample__Background__
#define __emptyExample__Background__

#include "ofMain.h"

class Background{
public:
    
    void setup();
    void update();
    void draw();
	void shuffle();
    
    vector<ofVec2f> points;
    
};

#endif /* defined(__emptyExample__Background__) */
