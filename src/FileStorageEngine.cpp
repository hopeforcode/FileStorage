/**
 * Author: Hou Wang
 * 
 * Application: sfarchiver
 * Association: file storage engine, command parser
 * 
 */

#include "FileStorageEngine.hpp"
#include "ArchiveFileBuffer.hpp"
#include "ArchiveMetadata.hpp"
#include <string>
#include <memory>
#include <iostream>
#include <algorithm>

namespace filestorage {

    const char* VERSION = "1.0";
    const char* APPNAME = "sfarchiver";
    const char* BUILDTIME = __DATE__;
    const std::fstream::openmode APPEND = std::fstream::out | std::fstream::binary | std::fstream::app;
    const std::fstream::openmode READ = std::fstream::in | std::fstream::binary;
    const std::fstream::openmode WRITE = std::fstream::out | std::fstream::binary;

    // helper functions:
    void showMessage(std::string msg) {
        std::cout << msg;
    }

    // implementations:

    FileStorageEngineBase* FileStorageEngineBase::mInstance = nullptr;

    FileStorageEngineBase::FileStorageEngineBase(){
        this->archiveStream = nullptr;
    }

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

        this->archiveStream = new std::fstream(archive, APPEND);
        std::fstream targetFileStream(targetPath, READ);

        if(targetFileStream.good() && this->archiveStream->good()) {
            MetaData meta;
            meta.setFileMetaData(targetPath);
            
            // write meta data to archive first
            *(this->archiveStream) << meta;

            // write file data block into archive
            FileBuffer buffer;

            while(!targetFileStream.eof()) {
                targetFileStream >> buffer;
                *(this->archiveStream) << buffer;
            }
        }

        // close targetFileStream and archiveStream
        this->archiveStream->flush();
        this->archiveStream->close();
        targetFileStream.close();
    }

    void FileStorageEngineBase::del(const std::vector<const char*>& args) {
        showMessage("Delete");
    }
    void FileStorageEngineBase::list(const std::vector<const char*>& args) {
        std::string archive(args[0]);

        if(this->archiveStream) {
            if(this->archiveStream->is_open()) this->archiveStream->close();
            delete this->archiveStream;
            this->archiveStream = nullptr;
        }

        this->archiveStream = new std::fstream(archive, READ);

        if(this->archiveStream->good()) {
            MetaData meta;
            // FileBuffer buffer;

            while(this->archiveStream->good()) {
                *(this->archiveStream) >> meta;
                if(this->archiveStream->good()){
                    std::string msg = meta.getFileName() + " " + std::to_string(meta.getFileSize()) + "Kb " + meta.getAddDate();
                    showMessage(msg);
                    this->archiveStream->seekg(meta.getFileSize() * sizeof(byte), std::fstream::cur);
                }
            }
        }

        this->archiveStream->flush();
        this->archiveStream->close();
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