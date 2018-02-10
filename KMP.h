//
// Created by anusha on 08.02.18.
//

#ifndef ARCADE_FINALPROJECT_KMP_H
#define ARCADE_FINALPROJECT_KMP_H



#include <iostream>
#include<string.h>
#include "StringSearch.h"


class KMP: public StringSearch{
private:
    std::string text;
    std::string pattern;
    unsigned txtLen;
    unsigned patLen;
    int *lps;

public:
    KMP();

    /***
     * Constructs an lps array for corresponding pattern lps[0..patternLength]
     * @param pattern - pattern to be preprocessed
     * @param text - text to be searched in
     */
    void init(std::string& text, std::string& pattern);

    void search();

};

#endif //ARCADE_FINALPROJECT_KMP_H
