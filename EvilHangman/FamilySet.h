#pragma once

#include <fstream>
#include <unordered_map>
#include <vector>
using namespace std;

class FamilySet
{
public:
    /* Function Description:
     * Get all the words from a dictionary that are of size len
     * Pre-Condition:
     * string representing the dictionary file, and a integer to represent
     * the wanted length size
     * Post-Condition:
     * wordlist will be populated with words from text file
     */
    FamilySet(string dictFile, int len);
	// Initializes from a word file where the word
	// must be of length len.

    /* Function Description:
     * Destroy every memory that has been allocated
     * Pre-Condition:
     * none
     * Post-Condition:
     * every instance of dictionaries second pair is deleted
     * dictionary is cleared
     * wordlist vector is deleted
     */
	~FamilySet();

    /* Function Description:
     * loop through every word in the word list and add the families onto the dictionary
     * by allocating a new vector
     * Pre-Condition:
     * a string letter representing the letter that was guess
     * a string guess pattern that represents the current state of the game
     * Post-Condition:
     * dictionaries will insert the filtered family if not found and push the word
     * that it can possibly be
     */
	void filterFamilies(string letter, string guessPattern);

    /* Function Description:
     * wordlist will be broken down to words found in the family
     * Pre-Condition:
     * a string representing the family we are looking at
     * Post-Condition:
     * wordlist will narrow down to a selected number of words
     * dictionaries will also get cleared
     */
	void setFamily(string family);

    /* Function Description:
     * gets a random word from the word list
     * Pre-Condition:
     * none
     * Post-Condition:
     * returns a random word from wordlist using the index generated
     */
    string getRandomWord();

    /* Function Description:
     * get the current words being stored in wordlist
     * Pre-Condition:
     * none
     * Post-Condition:
     * returns the vector wordlist
     */
	vector<string> getWords();

    /* Function Description:
     * Get the number of words in the wordlist
     * Pre-Condition:
     * none
     * Post-Condition:
     * returns the size of the wordlist
     */
    int numWords();

    /* Function Description:
     * Get the size of how many families there are in the dictionary
     * Pre-Condition:
     * none
     * Post-Condition:
     * returns the dictionaries size
     */
    int numFamilies();

    /* Function Description:
     * Returns how many words there are in the given family
     * Pre-Condition:
     * a string representing the family we are looking at
     * Post-Condition:
     * returns -1 if the family does not exist
     * returns the dictionary wordlist (second) size corresponding to the family(first)
     */
    int familySize(string family);

	// Iterator
    /* Function Description:
     * sets the iterator to the beginning of the dictionary
     * Pre-Condition:
     * none
     * Post-Condition:
     * famIter is assigned the beginning of the dictionary
     */
    void resetFamilyIter();


    /* Function Description:
     * Gets the current family name
     * Pre-Condition:
     * none
     * Post-Condition:
     * returns an empty string if the famIter is at the end of dictionaries
     * famIter is updated to the next family
     * returns the family famIter was before it was updated
     */
    string getNextFamily();
	
private:
    	// This stores all words currently "valid"
	vector<string>* wordlist;
	unordered_map<string, vector<string>*> dictionaries;

	// Used for Iterator.  The const_iterator is the same as an iterator
	// but used for situations where you want to prevent changes to the data.
	unordered_map<string, vector<string>*>::const_iterator famIter;
};

