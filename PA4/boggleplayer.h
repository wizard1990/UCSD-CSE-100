//
//  boggleplayer.h
//  PA4
//
//  Created by Yan Zhang on 11/27/13.
//  Copyright (c) 2013 Yan Zhang. All rights reserved.
//

//Yan Zhang A53050564
//Xiaoxiao Zheng A53044872

#ifndef __PA4__boggleplayer__
#define __PA4__boggleplayer__

#include "baseboggleplayer.h"
#include "boggleutil.h"
class LexiconTrie;
class LexiconTrieNode;

class BogglePlayer : public BaseBogglePlayer
{
private:
    //information of board
    vector<string> board;
    vector<bool> isUsed;
    int mRows;
    int mCols;
    LexiconTrie *dictionary;
    bool isDictionaryBuilt;
    bool isBoardSet;
    
    //private methods to calculate board string
    bool searchBoard(const string &word, int row, int col, vector<int> &track);
    //search valid words from given node in the dictionary,
    //save the result to the word
    void searchValidWords(int row, int col, LexiconTrieNode* node, int minLen, set<string>* word);
    int getIndex(int row, int col);
    void clearBoard();
    string toLowercase(string st);
public:
    //build the dictionary
    void buildLexicon(const set<string>& word_list);
    //initialize board
    void setBoard(unsigned int rows, unsigned int cols, string** diceArray);
    //computer calculation
    bool getAllValidWords(unsigned int minimum_word_length, set<string>* words);
    //look up word in the dictionary
    bool isInLexicon(const string& word_to_check);
    //look up word in the board
    vector<int> isOnBoard(const string& word_to_check);
    //customed board for test
    void getCustomBoard(string** &new_board, unsigned int *rows, unsigned int *cols);
    BogglePlayer();
    ~BogglePlayer();
};

#endif /* defined(__PA4__boggleplayer__) */

