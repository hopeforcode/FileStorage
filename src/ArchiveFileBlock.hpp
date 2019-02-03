/**
 * Author: Hou Wang
 *
 * Description: This file defines the file data block in archive
 */
#pragma once


#include <iostream>
namespace filestorage {
    typedef char byte;
    const int BLOCK_SIZE = 4096;    // the size of a file data block

    struct FileBlock {
        byte block[BLOCK_SIZE];
        
        friend std::istream& operator>>(std::istream& in, FileBlock& obj); 
        friend std::ostream& operator<<(std::ostream& out, FileBlock& obj); 
        void read(const std::istream& in);
        void write(std::ostream& out);
    };
}