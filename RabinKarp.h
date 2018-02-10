//
// Created by sid on 10.02.18.
//

#ifndef ARCADE_FINALPROJECT_RABINKARP_H
#define ARCADE_FINALPROJECT_RABINKARP_H

#include <iostream>
#include <regex>
#include "StringSearch.h"

class RabinKarp: public StringSearch {

    std::string text;
    std::string pattern;
    unsigned textLen;
    unsigned patternLen;
    long long currentHash;
    long long patternHash;
    int base = 256;
    const unsigned moduloPrime = 101;
    long long largestPow = 1;

public:

    RabinKarp();

    bool checkAlphaNumeric(std::string testStr[]);

    void comparelenghts();

    //implement rolling hash function
    void init(std::string& text, std::string& pattern);

    /**
     * Rolling hash for Rabin Karp
     * @param
     * @return
     */
    unsigned long updateHash(char outChar, char inChar);

    //  implement match function. Do we need a shift function?
    void search();
};


#endif //ARCADE_FINALPROJECT_RABINKARP_H
