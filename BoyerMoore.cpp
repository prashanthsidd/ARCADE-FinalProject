//
// Created by sid on 06.02.18.
//

#include "BoyerMoore.h"

BoyersMoore::BoyersMoore() {}

void BoyersMoore::init(std::string& text, std::string& pattern){

    this->pattern = pattern;
    this->srcString = text;

    //Record the pattern and text lengths into member vars
    patternLen = pattern.length();
    srcLen = srcString.length();

    //Initialize arrays for preprocessing
    f = new int[patternLen + 1];
    s = new int[patternLen + 1];

    for (int i = 0; i <= patternLen; ++i) {
        f[i] = 0;
        s[i] = 0;
    }
    occ = new int[alphaSize];

    // Preprocessing
    bcPreprocess();  //Bad character prerpocessing
    gsPreprocess1(); //Good suffix case 1 preprocessing
    gsPreprocess2(); //Good suffix case 2 preprocessing


}

void BoyersMoore::search(){
    //Start matching
    int alignment = 0, matchIndex;
    while(alignment <= srcLen - patternLen){
        matchIndex = patternLen - 1;
        while(matchIndex >= 0 && srcString[alignment + matchIndex] == pattern[matchIndex]) matchIndex--;
        if(matchIndex < 0){
            std::cout << "Match found at pos :: " << alignment << std::endl;
            alignment += s[0];
        }
        else {
            alignment += (matchIndex - occurance(srcString[alignment + matchIndex])) > s[matchIndex + 1]
                         ? matchIndex - occurance(srcString[alignment + matchIndex])
                         : s[matchIndex + 1];
        }
    }

}

void BoyersMoore::bcPreprocess(){
    //Initialize with zero
    for (int i = 0; i < alphaSize; ++i) {
        occ[i] = -1;
    }

    //Store the last index of each character in pattern
    for (int j = 0; j < patternLen; ++j) {
        occ[pattern[j]] = j;
    }
}
//Bad character rule:
unsigned BoyersMoore::occurance(char c){
    return occ[c];
}

//Case 1 for good suffix rule
void BoyersMoore::gsPreprocess1(){
    int suffIndex = patternLen, borderIndex = patternLen + 1;
    f[suffIndex] = borderIndex;

    //Loop through all possible suffixes
    while(suffIndex > 0){
        //Check for extension to left
        while(borderIndex <= patternLen && pattern[suffIndex - 1] != pattern[borderIndex-1]){
            //record the mismatch
            if(s[borderIndex] == 0)
                s[borderIndex] = borderIndex - suffIndex;
            borderIndex = f[borderIndex];
        }
        suffIndex--;
        borderIndex--;
        f[suffIndex] = borderIndex;

    }

/*    std::cout << "f  s " << std::endl;
    for (int i = 0; i <= patternLen; ++i) {
        std::cout << f[i] << " " << s[i] << std::endl;
    }*/
}

void BoyersMoore::gsPreprocess2(){
    int borderIndex;
    borderIndex = f[0];

    for (int i = 0; i <= patternLen; ++i) {
        if(s[i] == 0) s[i] = borderIndex;
        if(i == borderIndex) borderIndex = f[borderIndex];
    }
}

BoyersMoore::~BoyersMoore() {
    delete []f;
    delete []s;
    delete []occ;
}