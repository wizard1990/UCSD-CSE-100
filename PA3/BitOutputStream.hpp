//
//  BitOutputStream.h
//  PA3
//
//  Created by zhang yan on 11/2/13.
//  Copyright (c) 2013 zhang yan. All rights reserved.
//

//Yan Zhang A53050564
//Xiaoxiao Zheng A53044872

#ifndef __PA3__BitOutputStream__
#define __PA3__BitOutputStream__

#include <string>
#include <cstdio>
#include <cstring>
using namespace std;

typedef unsigned char byte;

class BitOutputStream
{
public:
    BitOutputStream() :
    mFile(0),
    byteOffset(0),
    bitOffset(0)
    {
        memset(buffer, 0, sizeof(buffer));
    }
    
    //interfaces that make BitOutputstream have the same behavior as standard C++ ofstream
    void open(const char* file);
    void close();
    bool is_open();
    friend BitOutputStream& operator<<(BitOutputStream& stm, const byte& bit);
    friend BitOutputStream& operator<<(BitOutputStream& stm, const unsigned int& num);
    
private:
    FILE *mFile;    //Use C-style file operation to improve performance
    byte buffer[BUFSIZ];  //keep a buffer of 1KB to decrease the time of I/O on disk
    int byteOffset;     //buffer offset for byte and bit
    int bitOffset;
    void flushBuffer(bool isFileEnd);   //output the content in the buffer to the file
};

#endif /* defined(__PA3__BitOutputStream__) */
