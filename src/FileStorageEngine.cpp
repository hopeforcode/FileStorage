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
#include <iostream>

namespace filestorage {

    const char* VERSION = "1.0";
    const char* APPNAME = "sfarchiver";
    const char* BUILDTIME = __DATE__;

    // helper functions:
    void showMessage(std::string msg) {
        std::cout << msg << std::endl;
    }

    void openFileRead(std::fstream* file,std::string path) {
        if(file) {
            if(file->is_open()) file->close();
            delete file;
        }

        file = new std::fstream(path, std::fstream::in | std::fstream::binary);
    }

    void openFileAppend(std::fstream* file, std::string path) {
        if(file) {
            if(file->is_open()) file->close();
            delete file;
        }

        file = new std::fstream(path, std::fstream::in | std::fstream::binary | std::fstream::app);
    }

    void openFileOverwrite(std::fstream* file, std::string path) {
        if(file) {
            if(file->is_open()) file->close();
            delete file;
        }

        file = new std::fstream(path, std::fstream::in | std::fstream::binary);
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