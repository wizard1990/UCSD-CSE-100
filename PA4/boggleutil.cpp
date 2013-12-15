//
//  boggleutil.cpp
//  PA4
//
//  Created by Yan Zhang on 11/27/13.
//  Copyright (c) 2013 Yan Zhang. All rights reserved.
//

#include "boggleutil.h"

class LexiconTrieNode{
public:
    char character;
    LexiconTrieNode* parent;
    LexiconTrieNode* left;
    LexiconTrieNode* mid;
    LexiconTrieNode* right;
    bool isWord;
    LexiconTrieNode():
    parent(0), left(0), mid(0), right(0), character(0x00), isWord(false){};
    LexiconTrieNode(char ch, LexiconTrieNode* p):
    character(ch), parent(p), left(0), mid(0), right(0), isWord(false){};
};

//private methods

//insert node of character
//if node is NULL, allocate one
LexiconTrieNode* LexiconTrie::insertCharacterToNode(char ch, LexiconTrieNode* node, LexiconTrieNode* parent)
{
    if (node) {
        return node;
    }
    else {
        node = new LexiconTrieNode(ch, parent);
        return node;
    }
}

//insert a word to the dictionary
//create the root for the first insertion
void LexiconTrie::insertWord(const string& word)
{
    if (word.length() == 0) {
        return;
    }

    LexiconTrieNode *node = root;
    LexiconTrieNode *parent = 0;
    bool midFlag = false;
    for (int i = 0; i < word.length(); i++) {
        //find the next character of parent
        while (node && node->character != word[i]) {
            parent = node;
            if (word[i] < node->character) {
                node = node->left;
            }
            else {
                node = node->right;
            }
            midFlag = false;
        }
        //if found, go down the mid
        if (node) {
            if (i == word.length() - 1) {
                node->isWord = true;
                break;
            }
            parent = node;
            node = node->mid;
            midFlag = true;
        }
        //if not found, insert all the characters left
        //to the mid sequencially
        else {
            if (parent) {
                if (midFlag) {
                    parent->mid = insertCharacterToNode(word[i], 0, parent);
                    node = parent->mid;
                }
                else {
                    if (word[i] < parent->character) {
                        parent->left = insertCharacterToNode(word[i], 0, parent);
                        node = parent->left;
                    }
                    else {
                        parent->right = insertCharacterToNode(word[i], 0, parent);
                        node = parent->right;
                    }
                }
            }
            else {
                root = insertCharacterToNode(word[0], 0, 0);
                node = root;
            }
            
            for (int j = i + 1; j < word.length(); j++) {
                node->mid = insertCharacterToNode(word[j], 0, node);
                node = node->mid;
            }
            node->isWord = true;
            break;
        }
    }
}

//clear the memory
void LexiconTrie::remove(LexiconTrieNode* node)
{
    if (!node) {
        return;
    }
    remove(node->left);
    remove(node->right);
    remove(node->mid);
    delete node;
}

//public interface
//to be called by boggleplayer
void LexiconTrie::buildLexicon(const vector<string> &stringVector)
{
    if (root) {
        remove(root);
    }
    for (int i = 0; i < stringVector.size(); i++) {
        insertWord(stringVector[i]);
    }
}

//to be called by boggleplayer
bool LexiconTrie::isInLexicon(const string& word)
{
    return findNextDie(0, word).second;
}

//key function of optimization
//return a pair of reached node and flag of word end
//thus the boggle player can start from the last node of previous search
//optimized the performance to about 0.1 second (ref is 10s)
pair<LexiconTrieNode*, bool> LexiconTrie::findNextDie(LexiconTrieNode *startNode, const string &st)
{
    LexiconTrieNode *node = startNode ? startNode->mid : root;
    if (!node) {
        return make_pair(node, false);
    }
    int flag = false;
    
    for (int i = 0; i < st.length(); i++) {
        while (node && node->character != st[i]) {
            if (st[i] < node->character) {
                node = node->left;
            }
            else {
                node = node->right;
            }
        }
        if (node) {
            if (i == st.length() - 1) {
                if (node->isWord) {
                    flag = true;
                }
                break;
            }
            node = node->mid;
        }
        else break;
    }
    return make_pair(node, flag);
}

//get the word of the characters
//from the root to current node
string LexiconTrie::getWordToNode(LexiconTrieNode* node)
{
    string s;
    if (node) {
        s.insert(0, 1, node->character);
        while (node) {
            LexiconTrieNode* parent = node->parent;
            if (parent && parent->mid == node) {
                s.insert(0, 1, parent->character);
            }
            node = node->parent;
        }
    }
    return s;
}

//constructor and destructor
LexiconTrie::LexiconTrie():root(0){}
LexiconTrie::~LexiconTrie()
{
    remove(root);
}