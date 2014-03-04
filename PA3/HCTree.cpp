//
//  HCNode.cpp
//  PA3
//
//  Created by zhang yan on 11/2/13.
//  Copyright (c) 2013 zhang yan. All rights reserved.
//

//Yan Zhang A53050564
//Xiaoxiao Zheng A53044872

#include "HCTree.hpp"
#include "BitInputStream.hpp"
#include "BitOutputStream.hpp"
#include <algorithm>
using namespace std;

void HCTree::deleteHCNode(HCNode *node)
{
    if (node) {
        deleteHCNode(node->c0);
        deleteHCNode(node->c1);
        delete node;
    }
}

//transform the tree from the inserted node
//maintain double link-list
HCNode* HCTree::transform(HCNode *node)
{
    HCNode *leader = node;
    if (leader->prev && leader->count > leader->prev->count) {
        leader = leader->prev;
    }
    else return node;
    
    while (leader->prev && leader->prev->count == leader->count ) {
        leader = leader->prev;
    }
    
    if (leader != node && leader != node->p) {
        HCNode tmp = HCNode(*node);

        node->p = leader->p;
        if (node->p) {
            if (node->p->c0 == leader) {
                node->p->c0 = node;
            }
            else node->p->c1 = node;
        }
        
        leader->p = tmp.p;
        if (leader->p) {
            if (leader->p->c0 == node) {
                leader->p->c0 = leader;
            }
            else leader->p->c1 = leader;
        }
        
        queue<HCNode *> bfsQueue;
        bfsQueue.push(root);
        while (!bfsQueue.empty()) {
            HCNode* node = bfsQueue.front();
            bfsQueue.pop();
            if (node->c1) {
                bfsQueue.push(node->c1);
                bfsQueue.push(node->c0);
            }
            if (!bfsQueue.empty()) {
                HCNode *nextNode = bfsQueue.front();
                node->next = nextNode;
                nextNode->prev = node;
            }
        }
    }
    
    return node;
}

void HCTree::splitZeroNode(int index, HCNode *node)
{
    zeroNodes[index] = zeroNodes[zeroNodes.size() - 1];
    zeroNodes.erase(zeroNodes.begin() + zeroNodes.size() - 1);
    HCNode *newNode = new HCNode(0, 0x00, 0, 0, zeroNode, node, 0);
    
    zeroNode->count = 1;
    zeroNode->c0 = newNode;
    zeroNode->c1 = node;
    zeroNode->next = node;
    
    node->prev = zeroNode;
    node->next = newNode;
    node->p = zeroNode;
    
    zeroNode = newNode;
}

HCTree::~HCTree(){
    deleteHCNode(root);
}

void HCTree::build(const vector<int> &freqs)
{
    if (isAdaptive) {
        return;
    }
    priority_queue<HCNode*, vector<HCNode*>, HCNodePtrComp> nodeHeap;
    int leaveCount = (int)freqs.size();
    for (int i = 0; i < leaveCount; i++) {
        if (freqs[i] != 0) {
            leaves[i] = new HCNode(freqs[i], i);
            nodeHeap.push(leaves[i]);  //initialize the origin queue and leaves[]
        }
    }
    leaveCount = (int)nodeHeap.size();   //count leaves
    
    while (nodeHeap.size() > 1) {  //loop while there are more than 1 node
        HCNode *node1 = nodeHeap.top();
        nodeHeap.pop();
        HCNode *node2 = nodeHeap.top();
        nodeHeap.pop();
        HCNode *mergedNode = new HCNode(node1->count + node2->count, 0x00); //0x00 is an invalid char in non-leave nodes
        mergedNode->c0 = node1;
        mergedNode->c1 = node2;
        node1->p = mergedNode;
        node2->p = mergedNode;
        nodeHeap.push(mergedNode);  //merge the 2 smallest node
    }
    if (!nodeHeap.empty()) {
        root = nodeHeap.top();
    }
    else root = 0;
}

void HCTree::encode(byte symbol, BitOutputStream &out) const
{
    HCNode* node = leaves[symbol];
    string symbolCode;
    if (!node->p) {
        symbolCode.insert(0, "0");
    }
    else {
        while (node->p) {
            HCNode* parent = node->p;
            
            //bottom-up traverse to get the symbol code
            if (parent->c0 == node) {
                symbolCode.insert(0, "0");
            }
            else {
                symbolCode.insert(0, "1");
            }
            node = node->p;
        }
    }
    for (int i = 0; i < symbolCode.size(); i++) {
        out<<(byte)symbolCode[i];
    }
}

void HCTree::adaptive_encode(byte symbol, BitOutputStream &out)
{
    HCNode* node = leaves[symbol];
    string symbolCode;
    
    HCNode *downNode = node ? node : zeroNode;
    
    while (downNode->p) {
        HCNode* parent = downNode->p;
        
        //bottom-up traverse to get the symbol code
        if (parent->c0 == downNode) {
            symbolCode.insert(0, "0");
        }
        else {
            symbolCode.insert(0, "1");
        }
        downNode = downNode->p;
    }
    
    if (!node) {
        node = new HCNode(1, symbol);
        leaves[symbol] = node;

        for (int i = 0; i < zeroNodes.size(); i++) {
            if (symbol == zeroNodes[i]) {
                symbolCode += "10";
                splitZeroNode(i, node);
                break;
            }
            else {
                symbolCode += "1";
            }
        }
        
    }
    else {
        node->count++;
    }
    
    if (node->count == 1) {
        node = node->p;
    }

    while (node && node->p) {
        node = transform(node);
        node = node->p;
        node->count++;
    }
    
    for (int i = 0; i < symbolCode.size(); i++) {
        out<<(byte)symbolCode[i];
    }
}

void HCTree::writeHeader(BitOutputStream &out) const
{
    for (int i = 0; i < leaves.size(); i++) {
        if (!leaves[i]) {
            out << (unsigned int)0;
        }
        else out<<leaves[i]->count;
    }
}

byte HCTree::decode(BitInputStream &in) const
{
    //read a bit every single time
    //top-down trasverse to get the symbol
    HCNode *node = root;
    char ch;
    if (root->c0) {
        while (node->c0) {
            in>>ch;
            if (ch == '0') {
                node = node->c0;
            }
            else {
                node = node->c1;
            }
        }
    }
    else {
        in>>ch;
    }
    return node->symbol;
}

byte HCTree::adaptive_decode(BitInputStream &in)
{
    HCNode *node = root;
    char ch;
    byte symbol;
    while (node->c0) {
        in>>ch;
        if (ch == '0') {
            node = node->c0;
        }
        else {
            node = node->c1;
        }
    }
    if (node == zeroNode) {
        in>>ch;
        int index = 0;
        while (ch != '0') {
            in>>ch;
            index++;
        }
        symbol = zeroNodes[--index];
        node = new HCNode(1, symbol);
        leaves[symbol] = node;
        splitZeroNode(index, node);
    }
    else {
        symbol = node->symbol;
        node->count++;
    }
    
    if (node->count == 1) {
        node = node->p;
    }
    while (node && node->p) {
        node = transform(node);
        node = node->p;
        node->count++;
    }
    
    return symbol;
}

bool HCTree::isEmpty() const
{
    return root == 0;
}
