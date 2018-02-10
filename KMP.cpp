#include "KMP.h"

KMP::KMP() {}

void KMP::init(std::string& text, std::string& pattern) {

    this->text = text;
    this->pattern = pattern;

    txtLen = text.length();
    patLen = pattern.length();
    lps = new int[patLen];

    for (int k = 0; k < patLen; ++k) {
        lps[k] = 0;
    }

    lps[0]=0;
    int i=1,j=0;

    while (i<patLen){
        if(pattern[i]==pattern[j]){
            lps[i]=j+1;
            j++;
            i++;
        }
        else{

            if(j==0){
                lps[i]=0;
                i++;
            }
            else{
                j=lps[j-1];
            }
        }
    }
}

/***
 * Finds occurence of pattern[] in text[] using KMP search
 * @param text - complete text
 * @param pattern -  pattern to find in text
 */
void KMP::search() {

    int m=0,n=0;

    while(m<txtLen){
        if(pattern[n]==text[m]){
            m++;
            n++;
        }

        if(n==patLen){
            std::cout<<"String found at " << m-n <<std::endl;
            n=lps[n-1];
        }

        else if((m<txtLen)&&(pattern[n]!=text[m])){
            if(n!=0){
                n=lps[n-1];
            }
            else{
                m++;
            }
        }
    }

}