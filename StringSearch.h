//
// Created by sid on 09.02.18.
//

#ifndef ARCADE_FINALPROJECT_STRINGSEARCH_H
#define ARCADE_FINALPROJECT_STRINGSEARCH_H

#include <string>

//Parent class with pure virtual function for string matching algorithms
class StringSearch{

    //Method for preprocessing
    virtual void init(std::string& text, std::string& pattern) = 0;

    //Method for searching the pattern
    virtual void search() = 0;
};

#endif //ARCADE_FINALPROJECT_STRINGSEARCH_H
