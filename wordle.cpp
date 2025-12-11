#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void validWords(string combo, string floatingCombo, string ogInput, set<string>& valid, const set<string>& dict);
string floatingAndDashes(string ogInput, string floating);
void floatStringGen(string floating, string output, set<string>& combos);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    set<string> valid;
    set<string> combos; 
    string ogString = in;
    string floatingLetters = floating;
    string output = "";
    string combo = "";

    string floatingWDashes = floatingAndDashes(ogString, floatingLetters);
    
    floatStringGen(floatingWDashes, output, combos);

    //cout << "float string gen finished" << endl;

    for (string element : combos){
        //cout << "CURRENT COMBO: " << element << endl; 
        validWords(combo, element, ogString, valid, dict);
    }

    return valid; 
    
  
}

// Define any helper functions here
//takes a single floating combo and sees if it can be a validWord
void validWords(string combo, string floatingCombo, string ogInput, set<string>& valid, const set<string>& dict){
    if (ogInput.empty()){
        auto it = dict.find(combo);
        if (it != dict.end()){
            //cout << "VALID WORD TO INSERT IN VALID " << combo <<endl; 
            valid.insert(combo);
        }
        return;
    }
    else{
        string newFloatingCombo = floatingCombo;
        string newOgInput = ogInput;

        if (ogInput[0]!= '-'){
            newOgInput.erase(0,1);
            validWords(combo + ogInput[0], floatingCombo, newOgInput, valid, dict);
        }
        else {
            if (ogInput[0]== '-'){
                if (floatingCombo[0]=='-'){
                    newOgInput.erase(0,1);
                    newFloatingCombo.erase(0,1);
                    for (char letter = 'a'; letter <= 'z'; ++letter){
                        validWords(combo + letter, newFloatingCombo, newOgInput, valid, dict);
                    }
                }
                else{
                newOgInput.erase(0,1);
                newFloatingCombo.erase(0,1);
                validWords(combo + floatingCombo[0], newFloatingCombo, newOgInput, valid, dict);
            
                }
            }
            
        }
    }
}


void floatStringGen(string floating, string output, set<string>& combos)
{
    if (floating.empty()== true){
        //cout << output << endl;
        combos.insert(output);
        return;
    }
    else{
        for (size_t i=0; i<floating.size(); i++){
            char letter = floating[i];
            string newFloating = floating;
            newFloating.erase(i,1);
            floatStringGen(newFloating, output + letter, combos);
        }
    }
}

// this helper funct should generate the floating for the floatStringGen
string floatingAndDashes(string ogInput, string floating){
    size_t dashes = 0;
    string temp = floating;
    for(size_t i=0; i<ogInput.size(); i++){
        if (ogInput[i] == '-'){
            dashes++;
        }
        if (dashes>temp.size() && ogInput[i] == '-'){
            floating = floating + '-';
        }
    }
    return floating;
}