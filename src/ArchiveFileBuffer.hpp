/**
 * Author: Hou Wang
 *
 * Description: This file defines the file data block in archive
 */

#pragma once

#include <iostream>

namespace filestorage {

    typedef char byte;                  // define type byte
    const int BLOCK_SIZE = 4096;        // the size of a file data block

    struct FileBuffer {

        byte* block;         // array of bytes, 4Kb
        unsigned int size;

        FileBuffer() : FileBuffer(BLOCK_SIZE) {}

        FileBuffer(unsigned int s) {
            block = new byte[s];
            size = s;
            reset();
        }
        
        friend std::istream& operator>>(std::istream& in, FileBuffer& obj);     
        friend std::ostream& operator<<(std::ostream& out, FileBuffer& obj); 

        void read(std::istream& in);
        void read(std::istream& in, unsigned int bytes);
        void write(std::ostream& out);
        void reset();

        bool hasSubstr(std::string target);
    };
}