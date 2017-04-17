#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetFrameRate(60);
    ofSetBackgroundAuto(false);
    ofBackground(0);
    
    background.setup();
    
    delim = ' ';
    delim2 = '	';
    
//    font.loadFont("Eric Normal.ttf", 50);
//    fontInput.loadFont("Eric Normal.ttf", 70);    
    
    setTextSize(50);
    
    textInput.setup(&fontInput);
    
    loadDing.load("audio/ding.wav");
    
    fullText.clear();
    
    loadIgnoreWords();
    
    //readInText("text/macbeth.txt", true);
    loadAllText();
    
    for (int i=0; i<6; i++){
        ofSoundPlayer whooshSound;
        whooshSounds.push_back(whooshSound);
        whooshSounds[i].load("audio/whoosh"+ofToString(i)+".wav");
        whooshSounds[i].setMultiPlay(true);
        whooshSounds[i].setVolume(0.2);
    }
    
    bgSound.load("audio/rain_and_birds.mp3");
    bgSound.setVolume(0.9);
    bgSound.setLoop(true);
    bgSound.play();
    
    setWordsFromLine(fullText[ (int) ofRandom(fullText.size()) ]);
    
    ofEnableAlphaBlending();
    
}

//--------------------------------------------------------------
void ofApp::setTextSize(int newSize){
    curTextSize = newSize;
    font.load("FutuLt__.ttf", newSize);
    fontInput.load("FutuLt__.ttf", newSize+20);
}

//--------------------------------------------------------------
void ofApp::update(){
    deltaTime = ofGetElapsedTimef() - prevFrameTime;
    prevFrameTime = ofGetElapsedTimef();
    
    string lowerCaseEntry = toLowerCase(textInput.inputString);

    for (int i=0; i<curWords.size(); i++){
        curWords[i].update(deltaTime, lowerCaseEntry, curHighNumMatches);
    }
    
    textInput.update();
    background.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    //manual bg clear with transparency
    ofSetColor(0, 10);
    ofFill();
    ofDrawRectangle(0,0, ofGetWidth(), ofGetHeight());
    
    background.draw();
    
    //draw the words
    ofSetColor(255, 100);
    for (int i=0; i<curWords.size(); i++){
        curWords[i].draw();
    }
    
    textInput.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    textInput.keyPressed(key);
    
    if (textInput.checkInput){
        checkInput(textInput.inputString);
        textInput.checkInput = false;
        textInput.curInput.clear();
        //textInput.inputString = "";
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    if (x < 50 && y < 50){
		ofToggleFullscreen();
		background.shuffle();
    }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

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

//--------------------------------------------------------------
void ofApp::checkInput(string input){
    vector<string> possibleLines = getLinesWithSameWord(input, curLine);
    
    //was this a load command?
    string commandText = toLowerCase(input);
    if (commandText.find("load") == 0){
        
        //was it a special command?
        if (commandText == "loadall"){
            loadAllText();
        }else if (commandText == "loadrandom"){
            loadRandomText();
        }else{
            //otherwise, just try to load the given file
            string file = "text/" + commandText.substr(4, commandText.length()) + ".txt";
            cout<<"load:"<<file<<endl;
            loadText(file, true, true);
        }
    }
    
     if (commandText.find("textsize") == 0){
         string sizeText =  commandText.substr(8, commandText.length());
         if (isStringAPositiveNumber(sizeText)){
             int newTextSize = stoi(sizeText);
             setTextSize(newTextSize);
         }
     }
    
    if (possibleLines.size() > 0){
        setWordsFromLine( possibleLines[ (int)ofRandom(possibleLines.size()) ] );
    }else{
        setWordsFromLine( curLine );
    }
    
}

//--------------------------------------------------------------
void ofApp::setWordsFromLine(string line){
    //cout<<"------------"<<endl;
    
    curWords.clear();
    curLine = line;
    
    float textPaddingXMin = curTextSize*0.8f;   // 40;
    float textPaddingXMax = curTextSize*3;      //150;
    float textPaddingY = curTextSize*4;         //200;
    float xSpacingMin = curTextSize*0.5f;       //25;
    float xSpacingMax = curTextSize*0.9f;       //45;
    float ySpacing = curTextSize*1.5f;          //75;
    float ySPacingRange = curTextSize*0.6f;     //30;
    
    float timingOffsetStart = -0.1;
    float timingOffsetMin = 0.01;
    float timingOffsetMax = 0.2;
    
    
    vector<string> rawWords;
    string curWord = "";
    for (int i=0; i<line.length(); i++){
        if (line[i] == delim || line[i] == delim2){
            rawWords.push_back(curWord);
            curWord = "";
        }else{
            curWord += line[i];
        }
    }
    if (curWord.length() > 0){
        rawWords.push_back(curWord);
    }
    
    int curX = ofRandom(textPaddingXMin, textPaddingXMax);
    int curY = textPaddingY;
    float curTimeOffset = timingOffsetStart;
    
    for (int i=0; i<rawWords.size(); i++){
        Word thisWord;
        int numMatches = getLinesWithSameWord(rawWords[i], curLine).size();
        string lowercaseWord = toLowerCase(rawWords[i]);;
        bool isIgnoreWord = isWordAnIgnoreWord(lowercaseWord);
        if (isIgnoreWord){
            numMatches = 0;
        }
        thisWord.setup(rawWords[i], &font, &whooshSounds[ (int)ofRandom(whooshSounds.size())], curTimeOffset, numMatches);
        thisWord.lowercaseText = lowercaseWord;
        
        if (numMatches > curHighNumMatches){
            curHighNumMatches = numMatches;
        }
     
        if (curX + thisWord.width > ofGetWidth() - textPaddingXMin){
            curX = ofRandom(textPaddingXMin, textPaddingXMax);;
            curY += thisWord.height + ySpacing;
        }
        
        thisWord.setPos(curX, curY - ofRandom(ySPacingRange));
        curX += thisWord.width + ofRandom(xSpacingMin, xSpacingMax);
        curTimeOffset -= ofRandom(timingOffsetMin, timingOffsetMax);
        
        curWords.push_back(thisWord);
        //cout<<"ADD: "<<rawWords[i]<<endl;
    }
    
}

//--------------------------------------------------------------
vector<string> ofApp::getLinesWithSameWord(string targetWord, string lineToIgnore){
    vector<string> returnList;
    
    string targetLower = toLowerCase(targetWord);
    lineToIgnore = toLowerCase(lineToIgnore);
  //  cout<<"ignore line: "<<lineToIgnore<<endl;
    
    //go through the full text
    for (int i=0; i<fullText.size(); i++){
        string thisLine = fullTextLower[i];
        if (thisLine != lineToIgnore){
            size_t foundPos = thisLine.find(targetLower);
            if (foundPos < thisLine.length()){
                
                //cout<<"---------"<<endl;
                //cout<<thisLine<<endl;
                
                //make sure there is nothing before or after it
                bool stillGood = true;
                
                if (foundPos > 0){
                    if (thisLine[foundPos-1] != delim && thisLine[foundPos-1] != delim2){
                        stillGood = false;
                    }
                }
                
                if (foundPos + targetWord.length() < thisLine.length()){
                    
                    char testChar = thisLine[ foundPos+targetWord.length() ];
                    int testCharVal = (int)testChar;
                    //english characters
                    if ( (testCharVal >= 65 && testCharVal <= 90) || (testCharVal >= 97 && testCharVal <= 122) || (testCharVal >= 48 && testCharVal <= 57) ){
                        stillGood = false;
                    }
                    //still haven't figured out how to test for accented characters
                    
                }
                
                if (stillGood){
                    returnList.push_back(fullText[i]);
                }
            }
        }
    }
    
//    //tetsing
//    for (int i=0; i<returnList.size(); i++){
//        cout<<i<<":"<<returnList[i]<<endl;
//    }
    
    return returnList;
}

//--------------------------------------------------------------
string ofApp::toLowerCase(string input){
    string returnVal = input;
    for (int i=0; i<returnVal.length(); i++){
        returnVal[i] = tolower(returnVal[i]);
    }
    return returnVal;
}

//--------------------------------------------------------------
bool ofApp::isWordAnIgnoreWord(string input){
    for (int i=0; i<ignoreWords.size(); i++){
        if (ignoreWords[i] == input){
            return true;
        }
    }
    return false;
}

//--------------------------------------------------------------
bool ofApp::isStringAPositiveNumber(string input){
    for (int i=0; i<input.size(); i++){
        if (input[i]!='0' && input[i]!='1' && input[i]!='2' && input[i]!='3' && input[i]!='4' && input[i]!='5' && input[i]!='6' && input[i]!='7' && input[i]!='8' && input[i]!='9'){
            return false;
        }
    }
    return true;
}

//--------------------------------------------------------------
void ofApp::loadIgnoreWords(){
    ofBuffer buffer = ofBufferFromFile("ignore_words.txt");
    ignoreWords.clear();
    
    if (buffer.size()){
        
        while(buffer.isLastLine() == false){
            string line = buffer.getNextLine();
            
            ignoreWords.push_back( toLowerCase(line));
        }
    }
    else{
        cout<<"could not find ignore list"<<endl;
    }
    
    //cout<<"total ignore words: "<<ignoreWords.size()<<endl;
}

//--------------------------------------------------------------
void ofApp::loadAllText(){
    ofDirectory dir;
    dir.listDir("text");
    for (int i=0; i<dir.size(); i++){
        loadText(dir.getPath(i), i==0, i==dir.size()-1);
    }
}

//--------------------------------------------------------------
void ofApp::loadRandomText(){
    ofDirectory dir;
    dir.listDir("text");
    loadText(dir.getPath((int)ofRandom(dir.size())), true, true);
}

//--------------------------------------------------------------
void ofApp::loadText(string filename, bool clearText, bool playSound){
    
    ofBuffer buffer = ofBufferFromFile(filename);
    
    if (buffer.size()){
        if (clearText){
            fullText.clear();
            fullTextLower.clear();
        }
        
        while(buffer.isLastLine() == false){
            string line = buffer.getNextLine();
            
            if (line.length() > 5){
                
                string lowerLine = toLowerCase(line);
                fullText.push_back(line);
                fullTextLower.push_back(lowerLine);
            }
            
            
        }
        
        cout<<"loaded "<<filename;
        if (clearText){
            cout<<" and cleared the old text";
        }
        cout<<endl;
        
        if (playSound){
            loadDing.play();
        }
        
        curHighNumMatches = 0;
        
        setWordsFromLine(fullText[ (int) ofRandom(fullText.size()) ]);
        
    }
    else{
        cout<<"aint nothing there"<<endl;
    }
    
    cout<<"total lines: "<<fullText.size()<<endl;
}
