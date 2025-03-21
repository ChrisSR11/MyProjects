#include "Dictionary.h"
#include <fstream>

// Your code here
Dictionary::Dictionary()
{
    root = new Node;    //create a root
    numWords = 0;   //set the number of words to 0
}

Dictionary::~Dictionary() {
    destroyHelper(root);    //delete all nodes
}

Dictionary::Dictionary(const Dictionary &otherDict) {
    root = new Node;    //create a root
    numWords = 0;   //num of words starts as 0
    if(otherDict.numWords == 0) return;
    copyOther(otherDict);   //call the copy helper function

}

Dictionary::Dictionary(string filename) {
    root = new Node;    //create a root
    numWords = 0;   //set numwords to 0
    LoadDictionaryFile(filename);   //call the helper function
}

Dictionary &Dictionary::operator=(const Dictionary &otherDict) {
    if(this != &otherDict)  //if both this object and other object  are not the same address (Object)
    {
        MakeEmpty();
        copyOther(otherDict);   //then we copy the words in other to the *this object
        numWords = otherDict.numWords;
    }

    return *this;   //return the actual object
}

void Dictionary::LoadDictionaryFile(string filename) {
    ifstream fin;
    fin.open(filename); //open file

    string word;
    while(!fin.eof())   //while not at the end of file
    {
        fin >> word;    //get word from file
        AddWord(word);     //call add word to insert word
    }

    fin.close();    //close file
}

void Dictionary::SaveDictionaryFile(string filename) {
    ofstream out;   //output file stream variable
    out.open(filename);     //open the file
    SaveDictionaryHelper(root, "", out);    //call the helper function to save words in the file
    out.close();    //close file
}

void Dictionary::AddWord(string word) {
    if(IsWord(word)) return;    //duplicate
    Node* currNode = root;  //traversal Node
    for(int i = 0; i < word.size(); i++)    //loop through all chars in word
    {
        if('a' <= word[i] && word[i] <= 'z')    //chars are from [a,z]
        {
            int index = ((int)word[i]) - ((int) 'a');  //calculate the index to int
            if(currNode->letters[index] == nullptr)
                currNode->letters[index] = new Node;    //create new letter
            currNode = currNode->letters[index];
        }
        else
        {
            throw DictionaryError("Invalid character"); //throw exception
        }
    }
    currNode->isWord = true;    //set the word that was passed to true in the tree
    numWords++;     //increment counter
}

void Dictionary::MakeEmpty() {
    destroyHelper(root);    //destroy the tree
    root = new Node;    //initialize a new tree
    numWords = 0;   //set word count to 0
}

bool Dictionary::IsWord(string word) {

    Node* currNode = root;  //traversal Node
    for(int i = 0; i < word.size(); i++)    //loop through all chars in word
    {
        if('a' <= word[i] && word[i] <= 'z')    //chars are from [a,z]
        {
            if(currNode == nullptr) //checks to see if we are out of bounds
                return false;   //not a word

            int index = (int) word[i] - (int) 'a';  //calculate the index to int
            currNode = currNode->letters[index];    //traverse
        }
        else
        {
            throw DictionaryError("Invalid character"); //throw exception
        }

    }
    if(currNode != nullptr)     //if its not null then check to see if we have a word
        return currNode->isWord;
     return false;  //returns false and avoids out of bounds access from currNode
}

bool Dictionary::IsPrefix(string word) {

    Node* currNode = root;  //traversal Node
    for(int i = 0; i < word.size(); i++)    //loop through all chars in word
    {
        if(currNode == nullptr) //checks to see if we are out of bounds
            return false;

        if(word[i] < 'a' || word[i] > 'z')    //chars are from [a,z]
            throw DictionaryError("Invalid character"); //throw exception

        int index = (int) word[i] - (int) 'a';  //calculate the index to int
        currNode = currNode->letters[index];    //traverse
    }

    return true;    //if we exit loop then it's a prefix
}

int Dictionary::WordCount() {
    return numWords;
}

void Dictionary::copyOther(const Dictionary &otherDict) {
    MakeEmpty();    //empty the current tree
    numWords = otherDict.numWords;  //copy the number of words
    copyHelper(root, otherDict.root);   //call the copy helper function using the roots of *this object & other Object
}

void Dictionary::destroyHelper(Dictionary::Node *thisTree) {
    if(thisTree == nullptr) //if there is no node to destroy then return
        return;

    for(int i = 0; i < NUM_CHARS; i++)  //loop through every letter
        destroyHelper(thisTree->letters[i]);   //destory every node of the letter

    delete thisTree;    //destroys the root
}

void Dictionary::copyHelper(Dictionary::Node *&thisTree, Dictionary::Node *otherTree) {
    if(otherTree == nullptr)    //if the other node is empty
    {
        thisTree = nullptr;     //then the *this node is also empty
        return;
    }

    thisTree = new Node;        //create a new node that mimics to other node (deep copy)
    thisTree->isWord = otherTree->isWord;   //copies the isWord to tell if we reached a new word

    for(int i = 0; i < NUM_CHARS; i++)
        copyHelper(thisTree->letters[i], otherTree->letters[i]);    //do the same for every letter

}

void Dictionary::SaveDictionaryHelper(Dictionary::Node *curr, string currPrefix, ofstream &outFile) {
    if(curr == nullptr)     //if the current node is empty then return
        return;

    if(curr->isWord)
        outFile << currPrefix << endl;  //if we reached a word then print it out

    for(int i = 0; i < NUM_CHARS; i++)  //recurse to the next subtree and keep track of the current prefix
        SaveDictionaryHelper(curr->letters[i], (currPrefix + ((char) (i + (int) 'a'))), outFile);
}


