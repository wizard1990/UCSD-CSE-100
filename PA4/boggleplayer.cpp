//
//  boggleplayer.cpp
//  PA4
//
//  Created by Yan Zhang on 11/27/13.
//  Copyright (c) 2013 Yan Zhang. All rights reserved.
//

#include "boggleplayer.h"
#include <cstdlib>
#include <algorithm>

//private methods:

//calculate the linear index
int BogglePlayer::getIndex(int row, int col)
{
    if (row < 0 || col < 0 || row >= mRows || col >= mCols) {
        return -1;
    }
    return row * mCols + col;
}

//recursively search the word
bool BogglePlayer::searchBoard(const string &word, int row, int col, vector<int> &track)
{
    int index = getIndex(row, col);
    if (index < 0 || index >= board.size()) {
        return false;
    }
    if (isUsed[index]) {
        return false;
    }
    
    //compare length
    string cur = board[index];
    int curLen = (int)cur.length();
    int wordLen = (int)word.length();
    if (curLen > wordLen) {
        return false;
    }
    
    //get the substring and compare them
    if (word.substr(0, curLen) != cur) {
        return false;
    }
    
    track.push_back(index);
    
    if (wordLen == curLen) {
        return true;
    }
    
    isUsed[index] = true;
    string restStr = word.substr(curLen);
    
    //use static array to set the vector of movement
    static int step[8][2] = {-1, -1, -1, 0, -1, 1, 0, -1, 0, 1, 1, -1, 1, 0, 1, 1};
    for (int i = 0; i < 8; i++) {
        bool res = searchBoard(restStr, row + step[i][0], col + step[i][1], track);
        if (res) {
            isUsed[index] = false;
            return true;
        }
    }
    
    //recover the status of isUsed[]
    isUsed[index] = false;
    track.pop_back();
    return false;
}

//key function of optimization
//recursively search the word from the last reached node
//not need to start from the root every time
void BogglePlayer::searchValidWords(int row, int col, LexiconTrieNode *node, int minLen, set<string>* words)
{
    int index = getIndex(row, col);
    if (index < 0 || index >= board.size()) {
        return;
    }
    if (isUsed[index]) {
        return;
    }
    
    //get the search result
    //if not found, return immediately
    pair<LexiconTrieNode*, bool> searchResult = dictionary->findNextDie(node, board[index]);
    if (!searchResult.first) {
        return;
    }
    
    //flag the use records
    //if is the end of a word, add to the result words set
    isUsed[index] = true;
    if (searchResult.second == true) {
        string s = dictionary->getWordToNode(searchResult.first);
        if (s.length() >= minLen) {
            words->insert(s);
        }
    }
    //use a static array to save the step vector of 8 direction
    static int step[8][2] = {-1, -1, -1, 0, -1, 1, 0, -1, 0, 1, 1, -1, 1, 0, 1, 1};
    for (int i = 0; i < 8; i++) {
        searchValidWords(row + step[i][0], col + step[i][1], searchResult.first, minLen, words);
    }
    //restore the use records
    isUsed[index] = false;
}

void BogglePlayer::clearBoard()
{
    board.clear();
    isUsed.clear();
    mRows = mCols = 0;
    isBoardSet = false;
}

//get the lower case of string
string BogglePlayer::toLowercase(string st)
{
    string ans;
    int len = (int)st.length();
    for (int i = 0; i < len; i++) {
        ans += tolower(st[i]);
    }
    return ans;
}

//public interface:

void BogglePlayer::buildLexicon(const set<string>& word_list)
{
    //clear the old dictionary
    if (isDictionaryBuilt) {
        delete dictionary;
        dictionary = new LexiconTrie();
    }
    vector<string> v;
    for (set<string>::iterator iter = word_list.begin(); iter != word_list.end(); iter++) {
        v.push_back(*iter);
    }
    //shuffle the words to avoid the bad performance for ordered input
    random_shuffle(v.begin(), v.end());
    dictionary->buildLexicon(v);
    isDictionaryBuilt = true;
}

//initialize the board
void BogglePlayer::setBoard(unsigned int rows, unsigned int cols, string** diceArray)
{
    if (isBoardSet) {
        clearBoard();
    }
    mRows = rows;
    mCols = cols;
    
    //use a linear vector to represent the matrix
    for (int i = 0; i < mRows; i++) {
        for (int j = 0; j < mCols; j++) {
            board.push_back(toLowercase(diceArray[i][j]));
            isUsed.push_back(false);
        }
    }
    isBoardSet = true;
}

//get all valid words as requirements
bool BogglePlayer::getAllValidWords(unsigned int minimum_word_length, set<string>* words)
{
    if (!isDictionaryBuilt || !isBoardSet) {
        return false;
    }
    
    //search every grid as a start
    for (int i = 0; i < mRows; i++) {
        for (int j = 0; j < mCols; j++) {
            searchValidWords(i, j, 0, minimum_word_length, words);
        }
    }

    return true;
}

bool BogglePlayer::isInLexicon(const string& word_to_check)
{
    return dictionary->isInLexicon(word_to_check);
}

//return the track of given word
vector<int> BogglePlayer::isOnBoard(const string& word_to_check)
{
    vector<int> track;
    string word = toLowercase(word_to_check);
    
    //search every grid as a start
    for(int i = 0; i < mRows; i++)    {
        for(int j = 0; j < mCols; j++)        {
            if(searchBoard(word, i, j, track) ) {
                return track;
            }
        }
    }
    return track;
}

//customed board, using the same representation as simple board
void BogglePlayer::getCustomBoard(string** &new_board, unsigned int *rows, unsigned int *cols)
{
//    ifstream input("brd.txt");
//    input>>*rows;
//    input>>*cols;
//    
//    new_board = new string*[*rows];
//    for (int i = 0; i < *rows; i++) {
//        new_board[i] = new string[*cols];
//    }
//    
//    for (int i = 0; i < *rows; i++) {
//        for (int j = 0; j < *cols; j++) {
//            string s;
//            input>>s;
//            new_board[i][j] = s;
//        }
//    }
//    input.close();
//    setBoard(*rows, *cols, new_board);
}

//constructor and destructor
BogglePlayer::BogglePlayer():mRows(0), mCols(0), isDictionaryBuilt(false), isBoardSet(false)
{
    dictionary = new LexiconTrie();
}

BogglePlayer::~BogglePlayer()
{
    delete dictionary;
}
