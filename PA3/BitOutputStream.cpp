//
//  BitOutputStream.cpp
//  PA3
//
//  Created by zhang yan on 11/2/13.
//  Copyright (c) 2013 zhang yan. All rights reserved.
//

//Yan Zhang A53050564
//Xiaoxiao Zheng A53044872

#include "BitOutputStream.hpp"
#include <algorithm>

byte outputBitMap[8] = {
    static_cast<byte>(0x80),
    static_cast<byte>(0x40),
    static_cast<byte>(0x20),
    static_cast<byte>(0x10),
    static_cast<byte>(0x08),
    static_cast<byte>(0x04),
    static_cast<byte>(0x02),
    static_cast<byte>(0x01)};

//get file open status
bool BitOutputStream::is_open()
{
    if (mFile == 0) {
        return false;
    }
    return true;
}

//open a file
void BitOutputStream::open(const char* file)
{
    if (is_open()) {
        close();
    }
    mFile = fopen(file, "wb");
    if (!mFile) {
        printf("Cannot open the file.\n");
    }
    byteOffset = 0;
    bitOffset = 0;
}

//close the current file
void BitOutputStream::close()
{
    if (is_open()) {
        flushBuffer(true);
        fclose(mFile);
        mFile = 0;
        byteOffset = 0;
        bitOffset = 0;
    }
}

//flush the buffer when it is full or the input of file is finished
void BitOutputStream::flushBuffer(bool isFileEnd)
{
    if (isFileEnd) {
        if (bitOffset == 0) {
            fwrite(buffer, sizeof(byte), byteOffset, mFile);
            fwrite(outputBitMap, sizeof(byte), 1, mFile);
        }
        else {
            buffer[byteOffset] |= outputBitMap[bitOffset];
            fwrite(buffer, sizeof(byte), byteOffset+1, mFile);
        }
    }
    else {
        fwrite(buffer, sizeof(byte), sizeof(buffer), mFile);
    }
    byteOffset = 0;
    bitOffset = 0;
    memset(buffer, 0, sizeof(buffer));
}

//key method. input a byte which represents a bit into buffer.
//Flush the buffer if it is full
BitOutputStream& operator<<(BitOutputStream& stm, const byte& bit)
{
    if (!stm.is_open()) {
        return stm;
    }
    if (bit == '1') {
        unsigned char ch = outputBitMap[stm.bitOffset];
        stm.buffer[stm.byteOffset] |= ch;
    }
    stm.bitOffset++;
    if (stm.bitOffset == 8) {
        stm.bitOffset = 0;
        stm.byteOffset++;
        if (stm.byteOffset == BUFSIZ) {
            stm.flushBuffer(false);
        }
    }
    return stm;
}

//input a integer which records a frequency of symbol in the header. "\n" will be added automatically
BitOutputStream& operator<<(BitOutputStream& stm, const unsigned int& num)
{
    if (!stm.is_open()) {
        return stm;
    }
    //Another way to encode header
    //fwrite(&num, sizeof(int), 1, stm.mFile);
    fprintf(stm.mFile, "%d\n", num);
    return stm;
}