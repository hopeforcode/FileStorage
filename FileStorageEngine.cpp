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
    void showMessage(std::string msg) {
        std::cout << msg << std::endl;
    }

    void FileStorageEngineBase::add(Argument& arg) {
        showMessage("Add");
    }

    void FileStorageEngineBase::del(Argument& arg) {
        showMessage("Delete");
    }
    void FileStorageEngineBase ::list(Argument& arg) {
        showMessage("List");
    }
    
    void FileStorageEngineBase::getProps(Argument& arg) {
        showMessage("find");
    }
    
    void FileStorageEngineBase::extract(Argument& arg) {
        showMessage("Extract");
    }
    
    void FileStorageEngineBase::getVersion() {
        showMessage("Version");
    }
}