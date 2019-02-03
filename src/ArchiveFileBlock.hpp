/**
 * Author: Hou Wang
 *
 * Description: This file defines the file data block in archive
 */

#include <iostream>
namespace filestorage {
    typedef char byte;
    const int BLOCK_SIZE = 4096;    // the size of a file data block

    class FileBlock {
        private:
            byte block[BLOCK_SIZE];
        public:
            friend std::istream& operator>>(std::istream& in, FileBlock& obj); 
            friend std::ostream& operator<<(std::ostream& out, FileBlock& obj); 
    };
}