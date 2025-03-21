
#include "Dictionary.h"
#include "Boggle.h"
#include <fstream>

// Your code here

Boggle::Boggle()
{
    /*
     * The default constructor should initialize the dict
     * with words from dictionary.txt
     */
    string filename = "dictionary.txt";
    dict.LoadDictionaryFile(filename);

    /*
     * It initializes each entry of board to the empty string.
     * It should also initialize each entry of visited to false.
     */
    for(int i = 0; i < BOARD_SIZE; i++)
    {
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            board[i][j] = "";
            visited[i][j] = false;
        }
    }
}

Boggle::Boggle(string filename) {

    /*
     * This constructor should initialize the dict with words from filename.
     */

    dict.LoadDictionaryFile(filename);

    /*
     * It initializes each entry of board to the empty string.
     * It should also initialize each entry of visited to false.
     */
    for(int i = 0; i < BOARD_SIZE; i++)
    {
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            board[i][j] = "";
            visited[i][j] = false;
        }
    }
}

void Boggle::SetBoard(string (*board)[4]) {
    for(int i = 0; i < BOARD_SIZE; i++)
    {
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            this->board[i][j] = board[i][j];
        }
    }
}

void Boggle::SolveBoard(bool printBoard, ostream &output) {
    //clear the words found dictionary
    wordsFound.MakeEmpty();
    int count = 1;  //represents the number of steps taken from Start to Finish
    string prefix = ""; //represents the words found from start to finish
    for(int i = 0; i < BOARD_SIZE; i++)
    {
        for(int j = 0 ; j < BOARD_SIZE; j++)
        {
            SolveBoardHelper(i,j, count, prefix, printBoard, output);
        }
    }
}


void Boggle::SaveSolve(string filename) {
    wordsFound.SaveDictionaryFile(filename);
}

void Boggle::PrintBoard(ostream &output) {


    //print board can be either cout or ostream
    for(int i = 0; i < BOARD_SIZE; i++)     //loop boardsize times
    {
        for(int j = 0; j < BOARD_SIZE; j++)
        {
            if(visited[i][j] != 0)  //if visited is a numbers > 0
            {
                output << " '" << board[i][j] << "' ";  //then board data must be a visted 'letter'
            }
            else
            {
                output << "  " << board[i][j] << "  ";  //otherwise it was not visted
            }
        }

        output << "\t";     //tab

        for(int k = 0; k < BOARD_SIZE; k++)     //loop boardsize times for the visted 2D array
        {
            output << "  " << visited[i][k] << "  ";    //print its values
        }
        output << endl;     //end line for the new row
    }
}

/* Note:
 * This PrintBoard should be used by the SolveBoardHelper. (pass an ostream var to print to cout and possibly ostream)
 * SolveBoard is served as a wrapper to SolveBoardHelper. (pass bool var for printing to file or not)
 * pass row, col, and a prefix representing a word use for backtracking (similar to a maze)
 */

void Boggle::SolveBoardHelper(int row, int col, int count, string prefix, bool print, ostream& out) {
    //ALL BASE CASES THAT DETERMINES WHEN TO RETURN

    //base case 1: OUT OF BOUNDS
    if(row < 0 || col < 0 || row >= BOARD_SIZE || col >= BOARD_SIZE) return;

    //base case 2: REVISITING
    if(visited[row][col] != 0) return;

    //base case 3: PREFIX DNE IN DICTIONARY
    /* NOTE: if not use then we will be doing unnecessary exploring prefixes that we know will not be a word */
    if(!dict.IsPrefix(prefix)) return;

    //START EXPLORING:
    //current prefix
    prefix += board[row][col];  //add the letter from the starting position
    //keep track of visited vertices
    visited[row][col] = count;  //representing the x step

    //What if we found prefix that is a word in board? (output results)
    if(dict.IsWord(prefix) && !wordsFound.IsWord(prefix)) //found a word that DNE in wordsFound (case: duplicates)
    {
        wordsFound.AddWord((prefix));   //store the solved words in wordsFound dictionary
        /*The function also outputs the values to the output ostream object.
         * This ostream can be called with cout or an ofstream object */
        cout << "Word: " << prefix << endl;
        cout << "Number of Words: " << wordsFound.WordCount() << endl;
        PrintBoard(cout);

        if(print)   //show board prints to output file for every new valid word found in dict
        {
            out << "Word: " << prefix << endl;
            out << "Number of Words: " << wordsFound.WordCount() << endl;
            PrintBoard(out);
            out << endl;
        }
        else    //print the word count and word found to output file (like in example)
            out << wordsFound.WordCount() << "\t" << prefix << endl;
    }

    //North
    SolveBoardHelper(row - 1, col, count + 1, prefix, print, out);
    //Northeast
    SolveBoardHelper(row - 1, col + 1, count + 1, prefix, print, out);
    //East
    SolveBoardHelper(row, col + 1, count + 1, prefix, print,out);
    //Southeast
    SolveBoardHelper(row + 1, col + 1, count + 1, prefix, print, out);
    //South
    SolveBoardHelper(row + 1, col, count + 1, prefix, print, out);
    //Southwest
    SolveBoardHelper(row + 1, col - 1, count + 1, prefix, print, out);
    //West
    SolveBoardHelper(row, col - 1, count + 1, prefix, print, out);
    //Northwest
    SolveBoardHelper(row - 1, col - 1, count + 1, prefix, print, out);

    //backtracking to previous position
    visited[row][col] = 0;
}


// This function is done.
Dictionary Boggle::GetDictionary() {
    return dict;
}

// This function is done.
Dictionary Boggle::WordsFound() {
    return wordsFound;
}





