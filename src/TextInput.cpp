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
    //checking english characters
    if ((key >= 65 && key <= 90) || (key >= 97 && key <= 122) || key == 39){
        char thisChar = (char)key;
        string newEntry = " ";
        newEntry[0] = thisChar;
        curInput.push_back(newEntry);
        strokeSounds[ (int)ofRandom(strokeSounds.size())].play();
    }
    
    //checking international characters (kinda hacky)
    if (getInternationalCharacter(key) != ""){
        curInput.push_back(getInternationalCharacter(key));
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

string TextInput::getInternationalCharacter(int codePoint){
    
    //code point values from https://en.wikipedia.org/wiki/ISO/IEC_8859-1
    
    if (codePoint ==  170){
        return "ª";
    }
    if (codePoint == 181){
        return "µ";
    }
    if (codePoint == 186){
        return "º";
    }
    
    if (codePoint == 192){
        return "À";
    }
    if (codePoint == 193){
        return "Á";
    }
    if (codePoint == 194){
        return "Â";
    }
    if (codePoint == 195){
        return "Ã";
    }
    if (codePoint == 196){
        return "Ä";
    }
    if (codePoint == 197){
        return "Å";
    }
    if (codePoint == 198){
        return "Æ";
    }
    if (codePoint == 199){
        return "Ç";
    }
    if (codePoint == 200){
        return "È";
    }
    if (codePoint == 201){
        return "É";
    }
    if (codePoint == 202){
        return "Ê";
    }
    if (codePoint == 203){
        return "Ë";
    }
    if (codePoint == 204){
        return "Ì";
    }
    if (codePoint == 205){
        return "Í";
    }
    if (codePoint == 206){
        return "Î";
    }
    if (codePoint == 207){
        return "Ï";
    }
    
    if (codePoint == 208){
        return "Ð";
    }
    if (codePoint == 209){
        return "Ñ";
    }
    if (codePoint == 210){
        return "Ò";
    }
    if (codePoint == 211){
        return "Ó";
    }
    if (codePoint == 212){
        return "Ô";
    }
    if (codePoint == 213){
        return "Õ";
    }
    if (codePoint == 214){
        return "Ö";
    }
    //215 is skipped
    if (codePoint == 216){
        return "Ø";
    }
    if (codePoint == 217){
        return "Ù";
    }
    if (codePoint == 218){
        return "Ú";
    }
    if (codePoint == 219){
        return "Û";
    }
    if (codePoint == 220){
        return "Ü";
    }
    if (codePoint == 221){
        return "Ý";
    }
    if (codePoint == 222){
        return "Þ";
    }
    if (codePoint == 223){
        return "ß";
    }
    
    if (codePoint == 224){
        return "à";
    }
    if (codePoint == 225){
        return "á";
    }
    if (codePoint == 226){
        return "â";
    }
    if (codePoint == 227){
        return "ã";
    }
    if (codePoint == 228){
        return "ä";
    }
    if (codePoint == 229){
        return "å";
    }
    if (codePoint == 230){
        return "æ";
    }
    if (codePoint == 231){
        return "ç";
    }
    if (codePoint == 232){
        return "è";
    }
    if (codePoint == 233){
        return "é";
    }
    if (codePoint == 234){
        return "ê";
    }
    if (codePoint == 235){
        return "ë";
    }
    if (codePoint == 236){
        return "ì";
    }
    if (codePoint == 237){
        return "í";
    }
    if (codePoint == 238){
        return "î";
    }
    if (codePoint == 239){
        return "ï";
    }
    
    if (codePoint == 240){
        return "ð";
    }
    if (codePoint == 241){
        return "ñ";
    }
    if (codePoint == 242){
        return "ò";
    }
    if (codePoint == 243){
        return "ó";
    }
    if (codePoint == 244){
        return "ô";
    }
    if (codePoint == 245){
        return "õ";
    }
    if (codePoint == 246){
        return "ö";
    }
    //247 is skipped
    if (codePoint == 248){
        return "ø";
    }
    if (codePoint == 249){
        return "ù";
    }
    if (codePoint == 250){
        return "ú";
    }
    if (codePoint == 251){
        return "û";
    }
    if (codePoint == 252){
        return "ü";
    }
    if (codePoint == 253){
        return "ý";
    }
    if (codePoint == 254){
        return "þ";
    }
    if (codePoint == 255){
        return "ÿ";
    }
    return "";
}

string TextInput::getInput(){
    string returnVal = "";
    for (int i=0; i<curInput.size(); i++){
        returnVal += curInput[i];
    }
    return returnVal;
}
