//
//  TextInput.cpp
//  emptyExample
//
//  Created by Andy Wallace on 9/25/15.
//
//

#include "TextInput.h"


void TextInput::setup(ofTrueTypeFont * _font){
    font = _font;
    
    
    
    checkInput = false;
    
    enterSound.load("audio/enter.wav");
    enterSound.setMultiPlay(true);
    
    backspaceSound.load("audio/backspace.wav");
    backspaceSound.setMultiPlay(true);
    
    for (int i=0; i<4; i++){
        ofSoundPlayer keySound;
        keySound.load("audio/key"+ofToString(i)+".wav");
        keySound.setMultiPlay(true);
        strokeSounds.push_back(keySound);
    }
    
}

void TextInput::update(){
    
}

void TextInput::draw(){
    ofVec2f startPos;
    startPos.y = ofGetHeight() - 90;
    
    vector<float> xPositions;
    float spacingX = 5;
    float curX = 0;
    for (int i=0; i<curInput.size(); i++){
        float xOffset = 4 * ofNoise(ofGetElapsedTimef()*0.7, i, 10);
        float yOffset = -20 * ofNoise(ofGetElapsedTimef()*0.2, i, 20);
        
        float thisX = curX+xOffset;
        curX += spacingX;
        curX += font->stringWidth(curInput[i]);
        
        xPositions.push_back(thisX);
    }
    
    startPos.x = ofGetWidth()-200 - curX;
    
    ofSetColor(240, 100, 100, 100);
    
    for (int i=0; i<curInput.size(); i++){
        float yOffset = -20 * ofNoise(ofGetElapsedTimef()*0.2, i, 20);
        
        font->drawString(curInput[i], startPos.x + xPositions[i], startPos.y+yOffset);
    }
}

void TextInput::keyPressed(int key){
    
    if ( (key >= 65 && key <= 90) || (key >= 97 && key <= 122) || key == 39){
        char thisChar = (char)key;
        string newEntry = " ";
        newEntry[0] = thisChar;
        curInput.push_back(newEntry);
        strokeSounds[ (int)ofRandom(strokeSounds.size())].play();
    }
    
    //backspace
    if ( (key == 127 || key == 8) && curInput.size() > 0){
        curInput.erase(curInput.begin()+curInput.size()-1);
        backspaceSound.play();
    }
    
    //enter
    if (key == 13 && curInput.size() > 0){
        checkInput = true;
        enterSound.play();
    }
    
    inputString = getInput();
}

string TextInput::getInput(){
    string returnVal = "";
    for (int i=0; i<curInput.size(); i++){
        returnVal += curInput[i];
    }
    return returnVal;
}