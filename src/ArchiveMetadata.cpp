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
    
        if(sepPos != std::string::npos) {
            return filePath.substr(sepPos + 1, filePath.size() - (withExtension || dotPos != std::string::npos ? 1 : dotPos) );
        } else if(dotPos != std::string::npos) {
            return filePath;
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
        // in >> this->fileNameLen;
        in.read(reinterpret_cast<char*>(&this->fileNameLen), sizeof(this->fileNameLen));
        char *buffer = new char[this->fileNameLen];
        in.read(buffer, sizeof(char) * this->fileNameLen);
        this->fileName.assign(buffer, this->fileNameLen);

        // in >> this->fileExtLen;
        in.read(reinterpret_cast<char*>(&this->fileExtLen), sizeof(this->fileExtLen));
        char *extBuffer = new char[this->fileExtLen];
        in.read(extBuffer, sizeof(char) * this->fileExtLen);
        this->fileExtension.assign(extBuffer, this->fileExtLen);

        // // parse date added
        in.read(reinterpret_cast<char*>(&this->dateLen), sizeof(this->dateLen));
        char *dateBuffer = new char[this->dateLen];
        in.read(dateBuffer, sizeof(char) * this->dateLen);
        this->dateAdded.assign(dateBuffer, this->dateLen);

        // file size
        in.read(reinterpret_cast<char*>(&this->fileSize), sizeof(this->fileSize));
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
    }

    void MetaData::setFileMetaData(const std::string path) {
        int size = filestorage::getFileSize(path);
        this->fileSize = size;
        this->fileName = filestorage::getFileName(path);
        this->fileNameLen = this->fileName.size();
        this->fileExtension = getFileExtension(path);
        this->fileExtLen = this->fileExtension.size();

        auto today = std::chrono::system_clock::now();
        auto today_t = std::chrono::system_clock::to_time_t(today);
        std::string date = std::ctime(&today_t);
        this->dateAdded = date;
        this->dateLen = date.size();
    }
}