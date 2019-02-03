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
        char buffer[this->fileNameLen];
        in.read(buffer, sizeof(char) * this->fileNameLen);
        this->fileName.assign(buffer);

        in.read(reinterpret_cast<char*>(this->fileExtLen), sizeof(this->fileExtLen));
        char extBuffer[this->fileExtLen];
        in.read(extBuffer, sizeof(char) * this->fileNameLen * sizeof(char));
        this->fileExtension.assign(extBuffer);

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
        // write file name
        out.write(reinterpret_cast<char*>(this->fileNameLen), sizeof(this->fileNameLen));
        out << this->fileName;

        out.write(reinterpret_cast<char*>(this->fileExtLen), sizeof(this->fileExtLen));
        out << this->fileExtension;

        // parse date added
        out.write(reinterpret_cast<char*>(this->dayAdded), sizeof(day_t));
        out.write(reinterpret_cast<char*>(this->monthAdded), sizeof(month_t));
        out.write(reinterpret_cast<char*>(this->yearAdded), sizeof(year_t));

        // file size
        out.write(reinterpret_cast<char*>(this->fileSize), sizeof(this->fileSize));

        // file data blocks
        out.write(reinterpret_cast<char*>(this->blockOffsSize), sizeof(this->blockOffsSize));
        for (int i = 0; i < blockOffsSize; ++i) {
            out.write(reinterpret_cast<char *>(this->blockOffs[i]), sizeof(this->blockOffs[i]));
        }
    }
}