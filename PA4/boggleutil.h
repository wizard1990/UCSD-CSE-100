//
//  boggleutil.h
//  PA4
//
//  Created by Yan Zhang on 11/27/13.
//  Copyright (c) 2013 Yan Zhang. All rights reserved.
//

//Yan Zhang A53050564
//Xiaoxiao Zheng A53044872

#ifndef __PA4__boggleutil__
#define __PA4__boggleutil__

#include <vector>
#include <string>
#include <set>
using namespace std;
class LexiconTrieNode;

class LexiconTrie{
private:
    //insert a word to the tree
    void insertWord(const string& word);
    //insert a character as a node
    //return to the parent of inserted node
    LexiconTrieNode* insertCharacterToNode(char ch, LexiconTrieNode* node, LexiconTrieNode* parent);
    //clear the node and subtree
    void remove(LexiconTrieNode *node);
    
    LexiconTrieNode* root;
public:
    LexiconTrie();
    ~LexiconTrie();
    //buit the lexicon from a shuffled vector
    void buildLexicon(const vector<string>& stringVector);
    //search a word in the dictionary
    bool isInLexicon(const string& word);
    
    //return NULL if no match for the next die
    //if startNode is NULL, start from the root
    //used to optimize the finding of all words on board
    pair<LexiconTrieNode*, bool> findNextDie(LexiconTrieNode *startNode, const string& st);
    string getWordToNode(LexiconTrieNode* node);
};

#endif /* defined(__PA4__boggleutil__) */
