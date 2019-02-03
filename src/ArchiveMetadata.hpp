/**
 * Author: Hou Wang
 *
 * Description: This file defines the File metadata class for each file in archive.
 */

#pragma once

#include "ArchiveFileBlock.hpp"
#include <memory>

namespace filestorage {
    typedef unsigned short file_size_t;
    typedef unsigned short day_t;
    typedef unsigned short month_t;
    typedef unsigned short year_t;

    struct MetaData {
        const char *fileName;           // file name
        const char *fileExtension;      // extension name of a file
                                        // The date file is added
        day_t day_added;
        month_t month_added;
        year_t year_added;

        unsigned int fileSize;          // Size of a file

        unsigned int blockOffsSize;     // size of Array of block offsets after this metadata struct
        unsigned int * blockOffs;       // Array of block offsets after this metadata struct
    };

    class FileMetaData {
        public:
            
        private:
            std::unique_ptr<MetaData> m_metadata;
    };
}