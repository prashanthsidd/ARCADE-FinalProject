#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>
#include "vector"
#include "StringSearch.h"
#include "BoyerMoore.h"
#include "KMP.h"
#include "RabinKarp.h"


#define stepSize 5
#define minPatSize 5
#define maxPatSize 20

using namespace std;

class srcPatLenError{};

string getPatternString(unsigned len);

string ReadFromFile (std::string fPath) {
    string line;
    string entireText;
    ifstream myfile (fPath);
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            entireText+=line + " ";
        }
        myfile.close();

    }

    else cout << "Unable to open file. ";

    return entireText;

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

        //check for algol
        switch (algo){
            case 1: {
                std::cout << "Running Rabin Karp"<< std::endl;
                RabinKarp rabinKarp;
                rabinKarp.init(text, pattern);
                rabinKarp.search();
            }
                break;

            case 2: {
                std::cout << "Running KMP "<< std::endl;
                KMP kmp;
                kmp.init(text, pattern);
                kmp.search();
            }
                break;

            case 3: {
                std::cout << "Running Boyer Moore "<< std::endl;
                BoyersMoore boyersMoore;
                boyersMoore.init(text, pattern);
                boyersMoore.search();
            }
                break;

            case 4: return;

            default: std::cout << "Invalid search algorithm: Terminating..."<< std::endl;
                return;
        }

        std::cout << "\n\n";

    }
}

void batch(){
    //Get a file name. Read it and generate random strings/patterns to be searched
    std::string fPath;
    std::string text;
    std::string pattern;

    std::vector<StringSearch*> searchAlgos;

    searchAlgos.push_back(new BoyersMoore()) ;
    searchAlgos.push_back(new RabinKarp()) ;
    searchAlgos.push_back(new KMP()) ;

//    searchAlgos[1] = RabinKarp();

//    searchAlgos[2] = KMP();

    std::cout << "Please provide path of input file:";
    cin >> fPath;

    text = ReadFromFile(fPath);
    std::cout << text<< std::endl;

    //Run each string search algol 100 times on the given text and pattern and record performance
    //Generate a random string
    for (int k = 0; k < 1; ++k) {

        pattern = getPatternString(minPatSize + k * stepSize);
        pattern = "prash";
        std::cout<< "Searching for pattern : " << pattern << std::endl;

        for (int i = 0; i < 3; ++i) {
            cout<< "Running " << searchAlgos[i]->getAlgoName()<< endl;
            auto initTime = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> avgSeconds = initTime - initTime;
            for (int j = 0; j < 1000; ++j) {

                auto start = std::chrono::high_resolution_clock::now();

                searchAlgos[i]->init(text, pattern);
                searchAlgos[i]->search();

                auto end = std::chrono::high_resolution_clock::now();
                avgSeconds += end - start;

            }
            //Should write to a csv file
            std::cout << "Time taken by " << searchAlgos[i]->getAlgoName()
                      << " for 100 runs with pattern lenght " << pattern.length()
                      << " and text length " << text.length() << " : " << avgSeconds.count()/1000 << " ms \n\n";
        }
    }
    //Free the memory allocated to search algos
/*    for (int l = 0; l < searchAlgos.size(); ++l) {
        delete searchAlgos[l];
    }*/
}

string getPatternString(unsigned len) {
    string possibleChars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
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
            case 1: interactive();
                break;
            case 2: batch();
                break;
            case 3 : return 0;
        }
    }
}

