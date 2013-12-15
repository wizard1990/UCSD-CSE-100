//
//  BitInputStream.h
//  PA3
//
//  Created by zhang yan on 11/2/13.
//  Copyright (c) 2013 zhang yan. All rights reserved.
//

//Yan Zhang A53050564
//Xiaoxiao Zheng A53044872

#ifndef __PA3__BitInputStream__
#define __PA3__BitInputStream__

#include <cstdio>
#include <string>
#include <cstring>
using namespace std;

typedef unsigned char byte;

class BitInputStream
{
public:
    BitInputStream() :
    mFile(0),
    byteOffset(0),
    bitOffset(0),
    bufferTail(8 * sizeof(buffer)),
    isHeaderFinished(false)
    {
        memset(buffer, 0, sizeof(buffer));
    }
    
    //interfaces that make BitInputstream have the same behavior as standard C++ ifstream
    void open(const char* file);
    void close();
    bool is_open();
    bool eof();
    friend BitInputStream& operator>>(BitInputStream& stm, char& bit);
    friend BitInputStream& operator>>(BitInputStream& stm, int& num);
    
private:
    FILE *mFile;    //Use C-style file operation to improve performance
    byte buffer[BUFSIZ+1];  //keep a buffer of 1KB to decrease the time of I/O on disk, and +1 for lookAhead block
    int byteOffset;     //Buffer offset for byte and bit
    int bitOffset;
    int bufferTail;     //End-bit-index of the buffer. Used to handle the end-of-file.
    bool isHeaderFinished;  //determine whether head reading is finished
    void initialBuffer();   //initialize the buffer
    int refreshBuffer();    //refresh the buffer when it is empty
    void detectFileEnd(int offset);     //check the end bit in the buffer when end-of-file is reached
};

#endif /* defined(__PA3__BitInputStream__) */
