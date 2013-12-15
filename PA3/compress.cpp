//
//  compress.cpp
//  PA3
//
//  Created by zhang yan on 11/5/13.
//  Copyright (c) 2013 zhang yan. All rights reserved.
//

#include "HCTree.hpp"
#include "BitOutputStream.hpp"
#include <string>
#include <cstdio>
using namespace std;

//Yan Zhang A53050564
//Xiaoxiao Zheng A53044872

//traverse the file first to get the frequency of all bytes
//store it in the freq to build the HCTree
void collectWords(const string &file, vector<int> &freq, byte* buffer)
{
    FILE *fileHandle = fopen(file.c_str(), "rb");
    while (!feof(fileHandle)) {
        int byteCount = (int)fread(buffer, sizeof(byte), BUFSIZ*sizeof(byte), fileHandle);
        for (int i = 0; i < byteCount; i++) {
            freq[buffer[i]]++;
        }
    }
    fclose(fileHandle);
}

int main(int argc, const char * argv[])
{
    if (argc == 4) {
        if(string(argv[3]) != "-adaptive" && string(argv[3]) != "-a") {
            cout<<"Wrong input format.\n"<<endl;
            return -1;
        }
    }
    if (argc != 3 && argc != 4) {
        cout<<"Wrong input format.\n"<<endl;
        return -1;
    }
    //initialization
    //use a buffer to improve I/O performance
    string source(argv[1]);
    string object(argv[2]);
    bool isAdaptive = argc == 4;
    if (source == object) {
        printf("Please use different file name!\n");
        return -1;
    }
    HCTree *tree = new HCTree(isAdaptive);
    byte* buffer = (byte *)malloc(BUFSIZ*sizeof(byte));
    BitOutputStream bs;
    bs.open(object.c_str());
    FILE *srcFile = fopen(source.c_str(), "rb");
    
    if (!isAdaptive) {
        //first pass is only needed for non-adaptive
        vector<int> freq(256, 0);
        collectWords(source, freq, buffer);
        tree->build(freq);
        tree->writeHeader(bs);
    }
    
    while (!feof(srcFile)) {
        int byteCount = (int)fread(buffer, sizeof(byte), BUFSIZ, srcFile);
        if (isAdaptive) {
            for (int i = 0; i < byteCount; i++) {
                tree->adaptive_encode(buffer[i], bs);
            }
        }
        else {
            for (int i = 0; i < byteCount; i++) {
                tree->encode(buffer[i], bs);
            }
        }
    }
    
    //deallocation
    //free the memory in case of leak
    fclose(srcFile);
    bs.close();
    delete tree;
    free(buffer);
}