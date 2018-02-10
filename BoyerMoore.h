//
// Created by sid on 06.02.18.
//

#ifndef ARCADE_FINALPROJECT_BOYERSMOORE_H
#define ARCADE_FINALPROJECT_BOYERSMOORE_H

#include <string>
#include "StringSearch.h"
#include <iostream>


class BoyersMoore: public StringSearch{
private:

    std::string srcString;
    std::string pattern;
    int patternLen;
    int srcLen;
    int alphaSize = 256;
    //Pointer to an array of integers denoting starting point of largest border for each suffix of the pattern
    int* f;
    //Pointer to an array to store skips
    int* s;
    //Pointer to an array for bad character skip
    int* occ;

public:
    BoyersMoore();

    void init(std::string& text, std::string& pattern);

    void bcPreprocess();

    //Bad character rule:
    unsigned occurance(char c);

    //Case 1 for good suffix rule
    void gsPreprocess1();

    void gsPreprocess2();

    void search();

    std::string getAlgoName();

    ~BoyersMoore();
};



#endif //ARCADE_FINALPROJECT_BOYERSMOORE_H
