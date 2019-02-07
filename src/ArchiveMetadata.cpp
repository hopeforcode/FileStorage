/**
 * Author: Hou Wang
 *
 * Description: This file defines the File metadata class for each file in archive.
 */


#include "ArchiveMetadata.hpp"
#include "ArchiveFileBuffer.hpp"
#include <fstream>
#include <chrono>
#include <ctime>

namespace filestorage {
    
    // Helper functions
    int getFileSize(std::string filename) {
        std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
        return in.tellg(); 
    }

    std::string getFileExtension(std::string filePath) {
        std::size_t dotPos = filePath.rfind('.');

        if(dotPos != std::string::npos) {
            return filePath.substr(dotPos + 1);
        }
        return "";
    }

    std::string getFileName(std::string filePath, bool withExtension = true, char seperator = '/') {
        // Get last dot position
        std::size_t dotPos = filePath.rfind('.');
        std::size_t sepPos = filePath.rfind(seperator);
    
        if(sepPos != std::string::npos)
        {
            return filePath.substr(sepPos + 1, filePath.size() - (withExtension || dotPos != std::string::npos ? 1 : dotPos) );
        }
        return "";
    }

    // Implementations
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
        in.read(reinterpret_cast<char*>(&this->fileNameLen), sizeof(this->fileNameLen));
        char buffer[this->fileNameLen];
        in.read(buffer, sizeof(char) * this->fileNameLen);
        this->fileName.assign(buffer);

        in.read(reinterpret_cast<char*>(&this->fileExtLen), sizeof(this->fileExtLen));
        char extBuffer[this->fileExtLen];
        in.read(extBuffer, sizeof(char) * this->fileNameLen);
        this->fileExtension.assign(extBuffer);

        // parse date added
        in.read(reinterpret_cast<char*>(&this->dateLen), sizeof(this->dateLen));
        char dateBuffer[this->dateLen];
        in.read(dateBuffer, sizeof(char) * this->dateLen);
        this->dateAdded.assign(dateBuffer);

        // file size
        in.read(reinterpret_cast<char*>(&this->fileSize), sizeof(this->fileSize));

        // file data blocks
        in.read(reinterpret_cast<char*>(&this->numOfBlocks), sizeof(this->numOfBlocks));
    }

    void MetaData::write(std::ostream& out) const{
        // write file name
        out.write(reinterpret_cast<const char*>(&this->fileNameLen), sizeof(this->fileNameLen));
        out << this->fileName;

        out.write(reinterpret_cast<const char*>(&this->fileExtLen), sizeof(this->fileExtLen));
        out << this->fileExtension;

        // parse date added
        out.write(reinterpret_cast<const char*>(&this->dateLen), sizeof(this->dateLen));
        out << this->dateAdded;

        // file size
        out.write(reinterpret_cast<const char*>(&this->fileSize), sizeof(this->fileSize));

        // file data blocks
        out.write(reinterpret_cast<const char*>(&this->numOfBlocks), sizeof(this->numOfBlocks));
    }

    void MetaData::setFileMetaData(const std::string path) {
        int size = getFileSize(path);
        this->fileSize = size;
        this->fileName = getFileName(path);
        this->fileNameLen = this->fileName.size();
        this->fileExtension = getFileExtension(path);
        this->fileExtLen = this->fileExtension.size();
        this->numOfBlocks = (this->fileSize + BLOCK_SIZE - 1) / BLOCK_SIZE;

        auto today = std::chrono::system_clock::now();
        auto today_t = std::chrono::system_clock::to_time_t(today);
        std::string date = std::ctime(&today_t);
        this->dateAdded = date;
    }
}