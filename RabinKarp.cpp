//
// Created by sid on 10.02.18.
//

#include "RabinKarp.h"

RabinKarp::RabinKarp() {}


//check for alpha numeric
bool RabinKarp::checkAlphaNumeric(std::string testStr[]){
    std::regex alphaNum("[^a-b0-9]", std::regex::icase);
    return std::regex_search(*testStr, alphaNum);
}

//sanity checks
void RabinKarp::comparelenghts(){
    if(textLen < patternLen){
        //throw exception
//            throw srcPatLenError();
    }
}

//implement rolling hash function
void RabinKarp::init(std::string& text, std::string& pattern){

    this->text = text;
    textLen = text.length();

    this->pattern = pattern;
    patternLen = pattern.length();

    largestPow = 1;
    currentHash = 0;
    patternHash = 0;

    //get hash for both pattern and string
    for (int j = 0; j < patternLen - 1; ++j) {
        largestPow = (largestPow * base) % moduloPrime;
    }
    for (int i = 0; i < patternLen; ++i) {
        patternHash = (pattern[i] + patternHash * base) % moduloPrime;
        currentHash = (text[i] + currentHash * base) % moduloPrime;
    }
}


unsigned long RabinKarp::updateHash(char outChar, char inChar){
    // Apply the rolling hash function to update the hash
    currentHash = ((currentHash - outChar * largestPow) * base + inChar ) % moduloPrime;

    if(currentHash < 0)
        currentHash += moduloPrime;

    return currentHash;
}

unsigned long RabinKarp::search(){

    unsigned  long matches = 0;
    for (int i = 0; i <= textLen - patternLen; ++i) {

        //check for hash and string match
        if (patternHash == currentHash && pattern.compare(0, patternLen, text, i, patternLen) == 0) {
//            std::cout << "string match at pos :: " << i << std::endl;
            matches++;
        }

        updateHash(text[i], text[i + patternLen]);
    }
    return matches;
}

std::string RabinKarp::getAlgoName(){
    return "Rabin Karp";
}
