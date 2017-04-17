//
//  Word.cpp
//  emptyExample
//
//  Created by Andy Wallace on 9/25/15.
//
//

#include "Word.h"


void Word::setup(string _text, ofTrueTypeFont * _font, ofSoundPlayer * _sound,  float _timer, int _numMatches){
    text = _text;
    font = _font;
    
    timer = _timer;
    sound = _sound;
    hasPlayedSound = false;
    
    numMatches = _numMatches;
    
    width = font->getStringBoundingBox(text, 0, 0).width;
    height = font->getStringBoundingBox(text, 0, 0).height;
    
    seed = ofRandom(0,9999);
}

void Word::setPos(float x, float y){
    anchorPos.set(x,y);
    pos = anchorPos;
}


void Word::update(float deltaTime, string curEntry, int highNumMatches){
    timer += deltaTime;
    
    
    float range = font->getLineHeight()*0.5f;//40;
    float speed = 0.1;
    
    ofVec2f shake(0,0);
    
    int highShakeMatchNumber = MIN(20, highNumMatches/4);
    
    if (numMatches > 1){
        speed = ofMap(numMatches, 0, highShakeMatchNumber, 0.1, 0.2, true);// 0.1;
    }
    
    if (numMatches > 5){
        float shakeVal = ofMap(numMatches, 1, highNumMatches*0.75, 0, 3.5, true);
        shake.x = ofRandom(-shakeVal, shakeVal);
        shake.y = ofRandom(-shakeVal, shakeVal);
    }
    
    pos.x = anchorPos.x -range/2 + ofNoise(ofGetElapsedTimef()*speed, seed) * range + shake.x;
    pos.y = anchorPos.y -range/2 + ofNoise(ofGetElapsedTimef()*speed, seed, 100) * range + shake.y;
    
    showAltColor = false;
    size_t findPos = lowercaseText.find(curEntry);
    if (findPos == 0 && curEntry.length() > 0){
        showAltColor = true;
        
        //the text either has to fill it up or be followed by a single non-letter
        if (curEntry.length() < lowercaseText.length()){
            if (curEntry.length() < lowercaseText.length() -1){
                showAltColor = false;
            }else{
                char testChar = lowercaseText[curEntry.length()];
                int testCharVal = (int)testChar;
                if ( (testCharVal >= 65 && testCharVal <= 90) || (testCharVal >= 97 && testCharVal <= 122) || (testCharVal >= 48 && testCharVal <= 57) ){
                    showAltColor = false;
                }
            }
        }
        
        
    }
    
}

void Word::draw(){
    
    float alpha = 0;
    float maxAlpha = 50;
    if (timer > 0 ){
        alpha = timer * maxAlpha;
        alpha = MAX(alpha, maxAlpha);
        if (!hasPlayedSound){
            sound->play();
            hasPlayedSound = true;
        }
    }
    
    if (showAltColor){
        ofSetColor(252, 213, 53, alpha);
    }else{
        float whiteVal = ofMap(ofNoise(ofGetElapsedTimef()*0.3, seed, 200), 0, 1, 140, 400);
        
         ofSetColor(MIN(whiteVal,255), alpha);
    }
    
    font->drawString(text, pos.x, pos.y);
}
