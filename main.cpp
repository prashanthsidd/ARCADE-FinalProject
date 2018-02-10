#include <iostream>
#include <fstream>
#include "BoyerMoore.h"
#include "KMP.h"
#include "RabinKarp.h"

using namespace std;

class srcPatLenError{};

string ReadFromFile () {
    string text;
    string entireText;
    ifstream myfile ("/home/sid/CLionProjects/ARCADE-FinalProject/data.txt");
    if (myfile.is_open())
    {
        while ( getline (myfile,text) )
        {
            entireText+=text + " ";
        }
        myfile.close();

    }

    else cout << "Unable to open file. ";

    return entireText;

}


int main() {
    string inp;
    string text;
    string pattern;
    int algo;
    char fromFile = 'n';
    while (1){

        std::cout<< "Read from file? [y/n] :";
        getline(cin, inp);
        stringstream(inp) >> fromFile;
        if(fromFile != 'y') {
            std::cout << "Enter text string : ";
            getline(cin, text);

            std::cout << "Enter pattern string : ";
            getline(cin, pattern);
        }
        else{
            //read from file
            text = ReadFromFile();
            pattern = "prashanth";
        }
        std::cout<< "Enter\n 1 for Rabin Karp\n 2 for KMP\n 3 for Boyer Moore  : ";
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

            default: std::cout << "Invalid search algorithm: Terminating..."<< std::endl;
                return 1;
        }

        std::cout << "\n\n";

    }
    return 0;
}

