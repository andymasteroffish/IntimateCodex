//
//  TextInput.h
//  emptyExample
//
//  Created by Andy Wallace on 9/25/15.
//
//

#ifndef __emptyExample__TextInput__
#define __emptyExample__TextInput__

#include "ofMain.h"

class TextInput{
public:
    
    void setup(ofTrueTypeFont * _font);
    void update();
    void draw();
    void keyPressed(int key);
    string getInternationalCharacter(int codePoint);
    string getInput();
    
    ofTrueTypeFont * font;
    vector<string> curInput;
    
    string inputString;
    
    bool checkInput;
    
    vector<ofSoundPlayer> strokeSounds;
    ofSoundPlayer enterSound;
    ofSoundPlayer backspaceSound;
    
};

#endif /* defined(__emptyExample__TextInput__) */
