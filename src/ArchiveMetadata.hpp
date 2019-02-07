/**
 * Author: Hou Wang
 *
 * Description: This file defines the File metadata class for each file in archive.
 */

#pragma once

#include <iostream>
#include <string>

namespace filestorage {
    
    typedef unsigned short file_size_t;

    class MetaData {
        private:
            unsigned int fileNameLen;       // file name length
            std::string fileName;           // file name
            unsigned int fileExtLen;        // extension name length
            std::string fileExtension;      // extension name of a file
                                            
            unsigned int dateLen;           // the length of string representing date added
            std::string dateAdded;          // the date file is added

            unsigned int fileSize;          // Size of a file
            unsigned int numOfBlocks;       // number of blocks in file
            
        public:
            MetaData() {
                this->fileNameLen = 0;
                this->fileExtLen = 0;
                this->dateLen = 0;
                this->fileSize = 0;
                this->numOfBlocks = 0;
            }
            friend std::istream& operator>>(std::istream& in, MetaData& obj);
            friend std::ostream& operator<<(std::ostream& out, const MetaData& obj);

            void read(std::istream& in);
            void write(std::ostream& out) const;
            void setFileMetaData(const std::string path);
            unsigned int getMetadataSize() {
                return sizeof(fileNameLen) + sizeof(fileExtLen) + sizeof(dateLen) + sizeof(fileSize) + sizeof(numOfBlocks) +
                sizeof(char) * (fileNameLen + fileExtLen + dateLen);
            }
            std::string toString() {
                std::string res;
                res = fileName + " " + fileExtension + " " + dateAdded + " " + std::to_string(fileSize) + " " + std::to_string(numOfBlocks);
            }
    };
}