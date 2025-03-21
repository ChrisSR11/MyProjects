#ifndef BOGGLE_BOGGLE_H
#define BOGGLE_BOGGLE_H

#include <string>
#include "Dictionary.h"

using namespace std;

const int BOARD_SIZE = 4;

class BoardNotInitialized {};

class Boggle {
public:
    /* Function Description:
     * Loads a dictionary txt file and sets the board and visited 2D arrays with default values
     * Pre-condition:
     * a working dictionary class w/ LoadDictionaryFile
     * Post condition:
     * Dict will be populated with words from file
     * All elements in the board will be initialized with the empty string
     * all elements in visited will be 0 (false) since no vertex has been visited
     *
     */
    Boggle();  // load "dictionary.txt" into dict

    /* Function Description:
     * Loads a dictionary file and sets the board and visited 2D arrays with default values
     * Pre-condition:
     * a string filename in working directory
     * Post Condition:
     * populate the dict variable with words from the filename
     * all elements in the board will be initialized with the empty string
     * all elements in visited will be 0 (false) since no vertex has been visited
     */
    explicit Boggle(string filename);  // load filename into dict

    /* Function Description:
     * Copy a board object to the current board object
     * Pre-condition:
     * a two 2D array representing a board of strings
     * Post-condition:
     * the current board 2D array deep copies every element from the passed board object
     */
    void SetBoard(string board[BOARD_SIZE][BOARD_SIZE]);


    /* Function Description:
     * Finds all the words on the current board store by the board variable
     * Pre-condition:
     * A boolean variable printBoard that determines if we print the board to file
     * A ostream variable output, that will print to either cout or file
     * A working SaveSolveHelper function
     * Post-condition:
     * WordsFound dictionary will be made empty, and populated with words found in the board
     */
    void SolveBoard(bool printBoard, ostream& output);


    /* Function Description:
     * Save the words found from a previous board to a file
     * Pre-condition:
     * a string filename in a working directory
     * Post-condition:
     * writes the words in wordsFound to a file
     */
    void SaveSolve(string filename);   // Saves all the words from the last solve.

    /* Function Description:
     * gets the dictionary
     * Pre-condition:
     * none
     * Post-condition:
     * returns the dict object
     */
    Dictionary GetDictionary();

    /* Function Description:
     * gets the words found dictionary
     * Pre-condition:
     * none
     * Post-condition:
     * returns the WordsFound dictionary object
     */
    Dictionary WordsFound();

private:
    Dictionary dict;
    Dictionary wordsFound;
    string board[BOARD_SIZE][BOARD_SIZE];
    int visited[BOARD_SIZE][BOARD_SIZE];

    /* Function Description:
     * should print out a board and the order in which a letter was visited
     * Pre-condition:
     * an ostream output parameter used for printing
     * Post-condition:
     * prints the board 2D array, and the visited 2D array
     */
    void PrintBoard(ostream& output);

    /* Function Description:
     * Finds all the words on a board using recursive backtracking.
     * Explores all paths originating at a row and col and does not revisit positions
     * Pre-Condition:
     * an integer variable row, and col that represents where we want to start exploring,
     * an integer variable count that counts all the steps taken from original position
     * a string prefix that stores letters upon every step taken
     * a boolean print variable that is used for printing to file or not
     * a ostream variable that represents that place we want to print to
     * Post-Condition
     * if the row and col are out of bounds we return from the function
     * if the row and col is a place we have already visited before then we return from the function
     * if the prefix is not found withing the dict then we return from the function
     * prefix will append the letters from the board
     * visited 2D array at row and col will hold a numeric value in the order we visited a letter in board, then represent 0 at the end
     * count will be incremented with each recursion call
     * if a word is found that is not in the WordsFound dictionary then we add that word to WordsFound
     * and print the wordCount and word onto the console (cout).
     * if print variable is true then the same will apply to the (ostream)
     */
    void SolveBoardHelper(int row, int col, int count, string prefix, bool print, ostream& out);
};

#endif //BOGGLE_BOGGLE_H
