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

        byte block[BLOCK_SIZE];         // array of bytes, 4Kb
        unsigned int size;

        FileBuffer() {
            size = 0;
            reset();
        }
        
        friend std::istream& operator>>(std::istream& in, FileBuffer& obj);     
        friend std::ostream& operator<<(std::ostream& out, FileBuffer& obj); 

        void read(std::istream& in);
        void write(std::ostream& out);
        void reset();
    };
}