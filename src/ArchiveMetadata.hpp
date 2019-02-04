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
    typedef unsigned short day_t;
    typedef unsigned short month_t;
    typedef unsigned short year_t;

    class MetaData {
        private:
            unsigned int fileNameLen;       // file name length
            std::string fileName;           // file name
            unsigned int fileExtLen;        // extension name length
            std::string fileExtension;      // extension name of a file
                                            // The date file is added
            day_t dayAdded;
            month_t monthAdded;
            year_t yearAdded;

            unsigned int fileSize;          // Size of a file

            unsigned int blockOffsSize;     // size of Array of block offsets after this metadata struct
            unsigned int *blockOffs;       // Array of block offsets after this metadata struct

        public:
            friend std::istream& operator>>(std::istream& in, MetaData& obj);
            friend std::ostream& operator<<(std::ostream& out, const MetaData& obj);

            void read(std::istream& in);
            void write(std::ostream& out) const;
    };
}