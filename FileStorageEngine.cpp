/**
 * Author: Hou Wang
 * 
 * Application: sfarchiver
 * Association: file storage engine, command parser
 * 
 */

#include "FileStorageEngine.hpp"
#include <iostream>

namespace filestorage {
    FileStorageEngineBase* FileStorageEngineBase::mInstance = nullptr;

    FileStorageEngineBase::FileStorageEngineBase(){

    }

    FileStorageEngineBase* FileStorageEngineBase::getInstance(){
        if(!FileStorageEngineBase::mInstance){
            FileStorageEngineBase::mInstance = new FileStorageEngineBase;
        }

        return FileStorageEngineBase::mInstance;
    }

    void showMessage(std::string msg) {
        std::cout << msg << std::endl;
    }

    void FileStorageEngineBase::add() {
        showMessage("Add");
    }

    void FileStorageEngineBase::del() {
        showMessage("Delete");
    }
    void FileStorageEngineBase ::list() {
        showMessage("List");
    }
    
    void FileStorageEngineBase::getProps() {
        showMessage("find");
    }
    
    void FileStorageEngineBase::extract() {
        showMessage("Extract");
    }
    
    void FileStorageEngineBase::getVersion() {
        showMessage("Version");
    }
}