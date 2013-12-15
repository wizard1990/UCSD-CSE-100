//
//  uncompress.cpp
//  PA3
//
//  Created by zhang yan on 11/5/13.
//  Copyright (c) 2013 zhang yan. All rights reserved.
//

//Yan Zhang A53050564
//Xiaoxiao Zheng A53044872

#include "HCTree.hpp"
#include "BitInputStream.hpp"
#include <string>
#include <cstdio>
using namespace std;

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
    BitInputStream bs;
    bs.open(source.c_str());
    if (!isAdaptive) {
        vector<int> freq(256, 0);
        for (int i = 0; i < 256; i++) {
            bs>>freq[i];
        }
        tree->build(freq);
    }
    byte* buffer = (byte *)malloc(BUFSIZ*sizeof(byte));
    int index = 0;
    FILE *originalFile = fopen(object.c_str(), "wb");
    
    //do the real work. Uncompress the source file into object file
    if (tree->isEmpty()) {
        //do nothing. emptyfile
    }
    else {
        while (!bs.eof()) {
            byte ch = isAdaptive ? tree->adaptive_decode(bs) : tree->decode(bs);
            buffer[index++] = ch;
            if (index == BUFSIZ) {
                index = 0;
                fwrite(buffer, sizeof(byte), BUFSIZ, originalFile);
            }
        }
        if (index > 0) {
            for (int i = 0; i < index; i++) {
                fwrite(buffer+i, sizeof(byte), 1, originalFile);
            }
        }
    }
    
    //deallocation
    //free the memory in case of leak
    bs.close();
    delete tree;
    fclose(originalFile);
    free(buffer);
}