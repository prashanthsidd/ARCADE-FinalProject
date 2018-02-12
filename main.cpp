#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>
#include "vector"
#include "StringSearch.h"
#include "BoyerMoore.h"
#include "KMP.h"
#include "RabinKarp.h"


#define stepSize 10
#define minPatSize 10
#define maxPatSize 100
#define inFilePath "data.txt"
#define outFilePath "out.csv"
#define avgRuns 50

using namespace std;

class srcPatLenError{};

std::string fText;

std::string validStrings[] = {"me", "the", "come", "employee", "Spaulding said", "for", "said" ,"for I had quite persuaded"};


string getPatternString(unsigned len);

string getPatternFromReadText(unsigned i);

void ReadFromFile () {
    string line;

    if(fText.length()) return;

    ifstream myfile (inFilePath);
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            fText+=line + " ";
        }
        myfile.close();

    }

    else cout << "Unable to open file. ";

}

void interactive(){
    string inp;
    string text;
    string pattern;
    int algo;
    while (1){

        std::cout << "Enter text string : ";
        getline(cin, text);

        std::cout << "Enter pattern string : ";
        getline(cin, pattern);

        std::cout<< "Enter\n 1 for Rabin Karp\n 2 for KMP\n 3 for Boyer Moore\n 4 to go back :";
        getline(cin, inp);
        stringstream(inp) >> algo;

        std::cout<< "\n\n";

        //Time the run
        auto initTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> dur = initTime - initTime;
        auto start = std::chrono::high_resolution_clock::now();

        //check for algol
        switch (algo){
            case 1: {
                std::cout << "Running Rabin Karp"<< std::endl;
                RabinKarp rabinKarp;
                rabinKarp.init(text, pattern);
                std::cout << "Number of matches :: " << rabinKarp.search() << std::endl;
            }
                break;

            case 2: {
                std::cout << "Running KMP "<< std::endl;
                KMP kmp;
                kmp.init(text, pattern);
                std::cout << "Number of matches :: " << kmp.search() << std::endl;
            }
                break;

            case 3: {
                std::cout << "Running Boyer Moore "<< std::endl;
                BoyersMoore boyersMoore;
                boyersMoore.init(text, pattern);
                std::cout << "Number of matches :: " << boyersMoore.search() << std::endl;
            }
                break;

            case 4: return;

            default: std::cout << "Invalid search algorithm: Terminating..."<< std::endl;
                return;
        }
        auto end = std::chrono::high_resolution_clock::now();
        dur = end - start;
        cout<< "Time taken : " << dur.count();
        std::cout << "\n\n";

    }
}

void batch(){
    //Get a file name. Read it and generate random strings/patterns to be searched
    std::string pattern;

    std::vector<StringSearch*> searchAlgos;

    searchAlgos.push_back(new BoyersMoore()) ;
    searchAlgos.push_back(new RabinKarp()) ;
    searchAlgos.push_back(new KMP()) ;


    std::cout << "Reading from file :" << inFilePath;

    //Open outputfile.
    ofstream outF;
    outF.open(outFilePath, ios::app);
    outF << "Text Length, Pattern Length, Time(ms), Algorithm \n";
    //Run each string search algol 100 times on the given text and pattern and record performance
    //Generate a random string
    for (int k = 0; pattern.length() < maxPatSize; ++k) {
//    for (int k = 0; k < 8; ++k) {
                pattern = getPatternString(minPatSize + k * stepSize);
//        pattern = validStrings[k];

        std::cout<< "Searching for pattern : " << pattern << std::endl;

        for (int i = 0; i < 3; ++i) {
            cout<< "Running " << searchAlgos[i]->getAlgoName()<< endl;

            auto initTime = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> avgSeconds = initTime - initTime;

            unsigned  long matches = 0;

            for (int j = 0; j < avgRuns; ++j) {

                auto start = std::chrono::high_resolution_clock::now();

                searchAlgos[i]->init(fText, pattern);
                matches += searchAlgos[i]->search();

                auto end = std::chrono::high_resolution_clock::now();
                avgSeconds += end - start;

            }

            outF << fText.length() << "," << pattern.length() << "," << avgSeconds.count() / avgRuns << "," << matches / avgRuns << "," << searchAlgos[i]->getAlgoName()<<"\n";
        }
    }
    outF.close();
    //Free the memory allocated to search algos
    for (int l = 0; l < searchAlgos.size(); ++l) {
        delete searchAlgos[l];
    }
}

string getPatternFromReadText(unsigned len) {
    int rangeMax = fText.length() - len;
    return fText.substr(rand() % rangeMax, len);
}

string getPatternString(unsigned len) {
    string possibleChars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789 ?\",.!\'-";
    string pattern;

    for (int k = 0; k < len; ++k) {
        char c = possibleChars[rand() % possibleChars.length()];
        pattern += c;
    }
    return pattern;
}

int main() {
    int mode;
    std::string inp;
    while (1){
        std::cout<< "Enter:\n    1 for interactive mode\n    2 for batch mode\n    3 to terminate : ";
        getline(cin, inp);
        stringstream(inp) >> mode;

        switch (mode){

            case 1:
                interactive();
                break;
            case 2:
                ReadFromFile();
                batch();
                break;
            case 3 : return 0;
        }
    }
}

