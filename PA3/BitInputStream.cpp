//
//  BitInputStream.cpp
//  PA3
//
//  Created by zhang yan on 11/2/13.
//  Copyright (c) 2013 zhang yan. All rights reserved.
//

//Yan Zhang A53050564
//Xiaoxiao Zheng A53044872

#include "BitInputStream.hpp"

//bitmap to modify the particular bit in a byte
byte inputBitMap[8] = {
    static_cast<byte>(0x80),
    static_cast<byte>(0x40),
    static_cast<byte>(0x20),
    static_cast<byte>(0x10),
    static_cast<byte>(0x08),
    static_cast<byte>(0x04),
    static_cast<byte>(0x02),
    static_cast<byte>(0x01)};

//get file open status
bool BitInputStream::is_open()
{
    if (mFile == 0) {
        return false;
    }
    return true;
}

//open a file
void BitInputStream::open(const char* file)
{
    if (is_open()) {
        close();
    }
    mFile = fopen(file, "rb");
    if (!mFile) {
        printf("Cannot open the file.\n");
    }
}

//close the current file
void BitInputStream::close()
{
    if (is_open()) {
        fclose(mFile);
        mFile = 0;
        byteOffset = 0;
        bitOffset = 0;
        bufferTail = 0;
    }
}

//determine if the end-of-file is reached
bool BitInputStream::eof()
{
    if (!is_open()) return true;
    if (!isHeaderFinished) {
        isHeaderFinished = true;
        initialBuffer();
    }
    if (bufferTail == BUFSIZ * 8) return false;
    if (byteOffset * 8 + bitOffset >= bufferTail) return true;
    else return false;
}

void BitInputStream::initialBuffer()
{
    byteOffset = 0;
    bitOffset = 0;
    memset(buffer, 0, sizeof(buffer));
    fread((void*)(buffer+BUFSIZ), sizeof(byte), 1, mFile);
    int num = refreshBuffer();
    
    //if end-of-file is reached indicated by num, detect the bit end
    if (num < 0) {
        close();
        printf("The file is broken.\n");
    }
    else if (num > 0) {
        detectFileEnd(num-1);
    }
    else {
        bufferTail = BUFSIZ * 8;
    }
}

//fill the buffer when it is empty and is still requested for bits
//return 0 if file is not ended, all the buffer is valid
//return the valid byte number of the buffer if reach the end-of-file
//return -1 if an error occured
int BitInputStream::refreshBuffer()
{
    bitOffset = 0;
    byteOffset = 0;
    buffer[0] = buffer[BUFSIZ];
    unsigned int size = (unsigned int)fread((void*)(buffer+1), sizeof(byte), BUFSIZ, mFile);    //set buffer from second byte
    if (size < BUFSIZ) {
        if (feof(mFile)) {
            return size + 1;
        }
        else return -1;
    }
    return 0;
}

//Precondition: the end-of-file is read to the buffer
//Postcondition: set the bufferTail by the right position
void BitInputStream::detectFileEnd(int offset)
{
    int pos;
    for(pos = 7; pos >= 0; pos--) {
        char c = buffer[offset] & inputBitMap[pos];
        if (c) break;
    }
    if (pos >= 0) {
        bufferTail = offset * 8 + pos;
    }
    else {
        bufferTail = -1;
    }
}

//key method. read the next bit in the file and save it as to a byte as 0 or 1
//automatically check the buffer status and refresh it if necessary
BitInputStream& operator>>(BitInputStream& stm, char& bit)
{
    if (!stm.is_open()) {
        return stm;
    }
    if (!stm.isHeaderFinished) {
        stm.isHeaderFinished = true;
        stm.initialBuffer();
    }
    if (stm.bitOffset + 8 * stm.byteOffset >= stm.bufferTail) {
        return stm;
    }
    
    unsigned char ch = stm.buffer[stm.byteOffset] & inputBitMap[stm.bitOffset];
    if (ch) {
        bit = '1';
    }
    else bit = '0';
    stm.bitOffset++;
    if (stm.bitOffset == 8) {
        stm.bitOffset = 0;
        stm.byteOffset++;
        if (stm.byteOffset == BUFSIZ) {
            int num = stm.refreshBuffer();
            
            //if end-of-file is reached indicated by num, detect the bit end
            if (num < 0) {
                stm.close();
                printf("The file is broken.\n");
            }
            else if (num > 0) {
                stm.detectFileEnd(num-1);
            }
        }
    }
    return stm;
}

//overload >> to write integers for header
BitInputStream& operator>>(BitInputStream& stm, int& num)
{
    if (!stm.is_open()) {
        return stm;
    }
    if (stm.isHeaderFinished) {
        return stm;
    }
    //Another way to decode header
    //fread((void *)&num, sizeof(int), 1, stm.mFile);
    char ch;
    fscanf(stm.mFile, "%d%c", &num, &ch);
    return stm;
}
