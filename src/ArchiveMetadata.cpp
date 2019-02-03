/**
 * Author: Hou Wang
 *
 * Description: This file defines the File metadata class for each file in archive.
 */


#include "ArchiveMetadata.hpp"

namespace filestorage {
    std::istream& operator>>(std::istream& in, MetaData& obj) {
        obj.read(in);
        return in;
    }

    std::ostream& operator<<(std::ostream& out, const MetaData& obj) {
        obj.write(out);
        return out;
    }

    void MetaData::read(std::istream& in) {
        // parse file name and extension
        in.read(reinterpret_cast<char*>(this->fileNameLen), sizeof(this->fileNameLen));
        if(this->fileName) {
            delete this->fileName;
            this->fileName = new char[this->fileNameLen + 1];
        }
        in.read(this->fileName, sizeof(char) * this->fileNameLen + 1);

        in.read(reinterpret_cast<char*>(this->fileExtLen), sizeof(this->fileExtLen));
        if(this->fileExtension) {
            delete this->fileExtension;
            this->fileExtension = new char[this->fileExtLen + 1];
        }
        in.read(this->fileExtension, sizeof(char) * this->fileNameLen * sizeof(char) + 1);

        // parse date added
        in.read(reinterpret_cast<char*>(this->dayAdded), sizeof(day_t));
        in.read(reinterpret_cast<char*>(this->monthAdded), sizeof(month_t));
        in.read(reinterpret_cast<char*>(this->yearAdded), sizeof(year_t));

        // file size
        in.read(reinterpret_cast<char*>(this->fileSize), sizeof(this->fileSize));

        // file data blocks
        in.read(reinterpret_cast<char*>(this->blockOffsSize), sizeof(this->blockOffsSize));
        if(this->blockOffs) {
            delete blockOffs;
            this->blockOffs = new unsigned int[this->blockOffsSize];
        }
        for (int i = 0; i < blockOffsSize; ++i) {
            in.read(reinterpret_cast<char *>(this->blockOffs[i]), sizeof(this->blockOffs[i]));
        }
    }

    void MetaData::write(std::ostream& out) const{

    }
}