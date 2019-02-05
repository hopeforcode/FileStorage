/**
 * Author: Hou Wang
 * 
 * Application: sfarchiver
 * Association: file storage engine, command parser
 * 
 */

#include "FileStorageEngine.hpp"
#include "ArchiveFileBlock.hpp"
#include "ArchiveMetadata.hpp"
#include <string>
#include <memory>
#include <iostream>

namespace filestorage {

    const char* VERSION = "1.0";
    const char* APPNAME = "sfarchiver";
    const char* BUILDTIME = __DATE__;
    const std::fstream::openmode APPEND = std::fstream::out | std::fstream::binary | std::fstream::app;
    const std::fstream::openmode READ = std::fstream::in | std::fstream::binary;
    const std::fstream::openmode WRITE = std::fstream::out | std::fstream::binary;

    // helper functions:
    void showMessage(std::string msg) {
        std::cout << msg << std::endl;
    }

    std::fstream* openFileRead(std::string path) {
        std::fstream* file = nullptr;
        file = new std::fstream(path, READ);
        return file;
    }

    std::fstream* openFileAppend(std::string path) {
        std::fstream* file = nullptr;
        file = new std::fstream(path, APPEND);
        return file;
    }

    std::fstream* openFileWrite(std::string path) {
        std::fstream* file = nullptr;
        file = new std::fstream(path, WRITE);
        return file;
    }

    // implementations:

    FileStorageEngineBase* FileStorageEngineBase::mInstance = nullptr;

    FileStorageEngineBase::FileStorageEngineBase(){}

    FileStorageEngineBase* FileStorageEngineBase::getInstance(){
        if(!FileStorageEngineBase::mInstance){
            FileStorageEngineBase::mInstance = new FileStorageEngineBase;
        }

        return FileStorageEngineBase::mInstance;
    }

    void FileStorageEngineBase::add(const std::vector<const char*>& args) {
        std::string archive(args[0]);
        std::string targetPath(args[1]);

        if(this->archiveStream) {
            if(this->archiveStream->is_open()) this->archiveStream->close();
            delete this->archiveStream;
            this->archiveStream = nullptr;
        }

        this->archiveStream = openFileAppend(archive);
        std::unique_ptr<std::fstream> targetFile(openFileRead(targetPath));
    }

    void FileStorageEngineBase::del(const std::vector<const char*>& args) {
        showMessage("Delete");
    }
    void FileStorageEngineBase ::list(const std::vector<const char*>& args) {
        showMessage("List");
    }
    
    void FileStorageEngineBase::getProps(const std::vector<const char*>& args) {
        showMessage("find");
    }
    
    void FileStorageEngineBase::extract(const std::vector<const char*>& args) {
        showMessage("Extract");
    }
    
    void FileStorageEngineBase::getVersion() {
        std::cout << APPNAME << " ";
        std::cout << "version " << VERSION << " ";
        std::cout << BUILDTIME << std::endl;
    }
}