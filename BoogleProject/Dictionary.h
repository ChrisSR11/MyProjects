#ifndef BOGGLE_DICTIONARY_H
#define BOGGLE_DICTIONARY_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;


const int NUM_CHARS = 26;

class DictionaryError{
public:
    /* Function Description: Sets the error message
     * Pre condition:
     * a string that represents the error msg
     * Post Condition:
     * sets the member variable messages to the argument msg
     */
    explicit DictionaryError(string msg) {
        this->msg = msg;
    }
    /* Function Description: gets a message
     * Pre condition: none
     * Post condition: the member variable messages is returned
     */
    string Msg(){
        return msg;  // returns king of flavor
    }
private:
    string msg;
};

class Dictionary
{

public:
    /* Function Description:
     * Default constructor will initialize a new tree
     * Pre Condition:
     * a root variable and numWords counter
     * Post Condition:
     * root will be set to a new node and numwords will be set to 0
     */
    Dictionary();

    /* Function Description:
     * Tree will become empty
     * Pre Condition:
     * destroy helper function working
     * Post Condition:
     * Deallocates all the nodes from root
     */
    ~Dictionary();  // I will not require this

    /* Function Description:
     * copy constructor, copies all the nodes from otherDict to the dictionary
     * Pre Condition:
     * another dictionary with words in it
     * Post Condition:
     * Dictionary will have the same data as otherDict
     */
    Dictionary(const Dictionary& otherDict);    // copy constructor

    /* Function Description:
     * constructor reads a file and adds every word to a dictionary from file
     * Pre Condition:
     * a text file being passed as a parameter to read the words from and
     * a working LoadDictionaryFile function.
     * Post Condition:
     * the dictionary class's root and word count will be updated with words from file
     */
    explicit Dictionary(string filename);       // The keyword explicit is used to tell the compiler
                                                // that this is not a conversion constructor.
    /* Function Description:
     * assigns the contents of otherDict to dictionary
     * Pre Condition:
     * another dictionary with words and data
     * Post Condition:
     * the dictionary object will deep copy every node's content from the other dictionary.
     * the dictionary object is returned from the function
     */
    Dictionary& operator=(const Dictionary& otherDict);

    /* Function Description:
     * loads all the words from a file to a dictionary
     * Pre Condition:
     *  a text file with words in it. A working addWord function to call
     * Post Condition:
     * root will have a path with words added from the file
     */
    void LoadDictionaryFile(string filename);

    /* Function Description:
     * write all the existing words from a dictionary onto file
     * Pre Condition:
     * an output file txt file to write the words, a root with words in it,
     * and a working SaveDictionaryHelper function to call upon
     * Post Condition:
     * the output text file will be populated with words from the dictionary
     */
    void SaveDictionaryFile(string filename);

    /* Function Description:
     * adds a word to the dictionary
     * Pre Condition:
     * a string word is required for this function to run
     * Post Condition:
     * an exception is thrown if the word contains char not from (a-z)
     * root will add letters from the word, and isWord will be modified to
     * indicate a word was added. The number of words counter is incremented
     */
    void AddWord(string word);

    /* Function Description:
     * erase all the words in dictionary and initialize a new dictionary.
     * Pre Condition:
     * a working destroyHelper function to call upon.
     * Post Condition:
     * all the nodes from the root will be destroyed, and root will be a new node
     * the number of words will be 0
     */
    void MakeEmpty();

    /* Function Description:
     * checks to see if the word given is a word in the dictionary
     * Pre Condition:
     * a string that represents a word
     * Post Condition:
     * an exception is thrown if a word contains bad values not from (a-z)
     * returns the true if a path was found from root to the end of the last char in word
     * and returns false if a path was not found
     */
    bool IsWord(string word);

    /* Function Description:
     * Checks to see if the given prefix is found in the dictionary
     * Pre Condition:
     * a word is given to traverse the dictionary.
     * The dictionary is initialized and contains words
     * Post Condition:
     * a false is returned if there are still characters in word and
     * dictionary no longer has nodes available from the path (currNode is null)
     * An exception is throw if the word contains bad values not from (a-z)
     * true is returned if a path from root to the last char in word exists
     */
    bool IsPrefix(string word);

    /* Function Description:
     * Gets the number of words in the dictionary
     * Pre Condition:
     * a member variable that indicates the word count
     * Post Condition:
     * the variable wordcount is returned
     */
    int WordCount();  // Returns total number of words in dictionary

private:

    class Node {
    public:
        // Your node structure here.
        // You can also use a struct if you like.

        // It is strongly recommended you create a constructor
        // to set default values
        Node* letters[NUM_CHARS];
        bool isWord = false;
        Node()
        {
            for(int i = 0; i < NUM_CHARS; i++)
                letters[i] = nullptr;
        }
    };

    Node* root;
    int numWords;

    // This function is used by the
    // copy constructor and the assignment operator.
    /* Function Description:
     * copies contents of given dictionary to current dictionary
     * Pre Condition:
     * The current tree is empty, and a working copy helper function
     * Post Condition:
     * the words and data associated are copied from the given dictionary
     * to the current dictionary
     */
    void copyOther(const Dictionary& otherDict);

    // Any private methods you need/want
    // You may change these helpers if you want, but you don't need to.
    /* Function Description:
     * a helper function that is used to delete all nodes in the tree for make empty
     * Pre Condition:
     * a node (thisTree) that represents the root of a tree
     * Post Condition:
     * The function is designed to handle the case where the provided root is a nullptr,
     * in which case it returns without attempting to destroy anything.
     * the nodes in the given tree from the specified root will be recursively destroyed
     */
    void destroyHelper(Node* thisTree);

    /* Function Description:
     * copies every node in the given dictionary to the current dictionary using recursion
     * Pre Condition:
     * two nodes, one representing the root of the current object, and the root
     * of the given (otherTree) tree.
     * Post Condition:
     * allocates memory and copies the isWord member variable of other tree onto current tree.
     * if the otherTree is nullptr then the current root is also nullptr.
     */
    void copyHelper(Node*& thisTree, Node* otherTree);

    /* Function Description:
     * recursively traverses a tree, and saves the words to an output file.
     * The function appends each word formed during the traversal to the output file
     * using the current prefix to build the complete words.
     * Pre Condition:
     * A node  that represents the current node in the tree we are on. a string
     * currPrefix to save the current prefix, and an output file txt.
     * Post Condition:
     * writes every word in dictionary onto the output file
     */
    void SaveDictionaryHelper(Node* curr, string currPrefix, ofstream& outFile);
};

#endif //BOGGLE_DICTIONARY_H
