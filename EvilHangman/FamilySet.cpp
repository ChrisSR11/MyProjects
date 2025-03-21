#include "FamilySet.h"
#include <fstream>
#include <iostream>

// Implementation of getRandomWord method
string FamilySet::getRandomWord() {
    int ind = rand() % wordlist->size();
    return wordlist->at(ind);
}

// Implementation of numWords method
int FamilySet::numWords() {
    return wordlist->size();
}

// Implementation of numFamilies method
int FamilySet::numFamilies() {
    return dictionaries.size();
}

// Implementation of getWords method
vector<string> FamilySet::getWords() {
    return *wordlist;
}

FamilySet::FamilySet(string dictFile, int len) {
    ifstream fin(dictFile);
    if (!fin.is_open())
        throw "ERROR OPENING FILE";

    wordlist = new vector<string>; // Create a new vector for wordlist
    string word;
    while (fin >> word) {   //place all words of len to wordlist
        if (word.size() == len)
            wordlist->push_back(word);
    }

    fin.close();
}

// Implementation of destructor
FamilySet::~FamilySet() {
    unordered_map<string, vector<string>*>::iterator it = dictionaries.begin();
    while(it != dictionaries.end())
    {
            delete it->second;
        it++;
    }

    dictionaries.clear(); // Clear the dictionaries map
    delete wordlist; // Deallocate memory for wordlist
}

void FamilySet::filterFamilies(string letter, string guessPattern) {
    //loop through every word in the current word list
    for (int i = 0; i < wordlist->size(); i++) {
        string word = wordlist->at(i);
        string family = word;   //used for filtering

        //construct family
            for (int j = 0; j < family.size(); j++) {
                //if wrong letter and guesspattern is * then transform to *
                if (family[j] != letter[0] && guessPattern[j] == '*')
                    family[j] = '*';
            }
        //cout << "WORD: " << word << " Letter: " << letter << " Guess pattern: " << guessPattern << " Family: " << family << endl;

        /*
         *  if (the family does NOT exist in dictionaries) {
         *  In dictionaries, associate family with a new vector
         */
        if(dictionaries.find(family) == dictionaries.end())
            dictionaries[family] = new vector<string>;

        //insert the filtered family and possible word it can be
        dictionaries[family]->push_back(word);
    }

}

void FamilySet::setFamily(string family) {
    //if the family is not found then the word list will be 0
    if(dictionaries.count(family) == 0)
    {
        wordlist = nullptr;
        return;
    }
    //update wordlist to the new guessprogress
    wordlist = dictionaries[family];
    //clear the dictionary to avoid **** being the largest family
    dictionaries.clear();
}

int FamilySet::familySize(string family) {
    if(dictionaries.count(family) == 0)
        return -1;

    //return all possible words in the family
    return dictionaries[family]->size();
}

// Implementation of resetFamilyIter method
void FamilySet::resetFamilyIter() {
    famIter = dictionaries.begin();
}

// Implementation of getNextFamily method
string FamilySet::getNextFamily() {
    if(famIter == dictionaries.end())   //if at end return empty string
        return "";
    string family = famIter->first; //get the current family
    famIter++;  //move to second family
    return family;  //return currfamily
}