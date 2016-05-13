//
//  Word.h
//  emptyExample
//
//  Created by Andy Wallace on 9/25/15.
//
//

#ifndef __emptyExample__Word__
#define __emptyExample__Word__

#include "ofMain.h"

class Word{
public:
    
    
    void setup(string _text, ofTrueTypeFont * _font, ofSoundPlayer * _sound, float _timer, int _numMatches);
    void setPos(float x, float y);
    void update(float deltaTime, string curEntry, int highNumMatches);
    void draw();
    
    string text, lowercaseText;
    ofTrueTypeFont * font;
    
    ofSoundPlayer * sound;
    bool hasPlayedSound;
    
    ofVec2f anchorPos;
    ofVec2f pos;
    
    int width;
    int height;
    
    float seed;
    
    int numMatches;
    
    float timer;
    
    bool showAltColor;
    
};

#endif /* defined(__emptyExample__Word__) */
