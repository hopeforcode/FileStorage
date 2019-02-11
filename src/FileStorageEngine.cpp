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
#include "Utils.hpp"
#include <string>
#include <memory>
#include <iostream>
#include <algorithm>
#include <cstdio>

namespace filestorage {

    const char* VERSION = "1.0";
    const char* APPNAME = "sfarchiver";
    const char* BUILDTIME = __DATE__;
    const char* TEMP_FILE = "tmp";

    const std::fstream::openmode APPEND = std::fstream::out | std::fstream::binary | std::fstream::app;
    const std::fstream::openmode READ = std::fstream::in | std::fstream::binary;
    const std::fstream::openmode WRITE = std::fstream::out | std::fstream::binary;

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
        if(args.size() != 2) {
            utils::showMessage("Number of Arguments doesn't match\n");
            return;
        }

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
        if(args.size() != 2) {
            utils::showMessage("Number of Arguments doesn't match\n-");
            return;
        }

        std::string archive(args[0]);
        std::string targetFileName(args[1]);

        if(this->archiveStream) {
            if(this->archiveStream->is_open()) this->archiveStream->close();
            delete this->archiveStream;
            this->archiveStream = nullptr;
        }

        // TODO: to complete:

        // stream for reading
        this->archiveStream = new std::fstream(archive, READ);
        // stream for compressing file after delete
        std::string tempFileName(TEMP_FILE);
        std::fstream archiveCopyStream(tempFileName, WRITE);

        if(this->archiveStream->good() && archiveCopyStream.good()) {
            MetaData meta;
            
            while(this->archiveStream->good()) {
                *(this->archiveStream) >> meta;

                if(this->archiveStream->good()) {
                    if(meta.getFileName() == targetFileName) {
                        this->archiveStream->seekg(meta.getFileSize() * sizeof(byte), std::fstream::cur);
                    } else {
                        archiveCopyStream << meta;
                        FileBuffer buffer;
                        buffer.read(*this->archiveStream, meta.getFileSize());
                        archiveCopyStream << buffer;
                    }
                }

                meta.reset();
            }
        }

        this->archiveStream->flush();
        this->archiveStream->close();
        archiveCopyStream.flush();
        archiveCopyStream.close();

        std::remove(archive.data());
        std::rename(tempFileName.data(), archive.data());
    }
    void FileStorageEngineBase::list(const std::vector<const char*>& args) {
        if(args.size() != 1) {
            utils::showMessage("Number of Arguments doesn't match");
            return;
        }
        std::string archive(args[0]);

        if(this->archiveStream) {
            if(this->archiveStream->is_open()) this->archiveStream->close();
            delete this->archiveStream;
            this->archiveStream = nullptr;
        }

        this->archiveStream = new std::fstream(archive, READ);

        if(this->archiveStream->good()) {
            MetaData meta;

            while(this->archiveStream->good()) {
                *(this->archiveStream) >> meta;
                if(this->archiveStream->good()){
                    utils::showMessage(meta.toString());
                    this->archiveStream->seekg(meta.getFileSize() * sizeof(byte), std::fstream::cur);
                }
                meta.reset();
            }
        }

        this->archiveStream->flush();
        this->archiveStream->close();
    }
    
    void FileStorageEngineBase::getProps(const std::vector<const char*>& args) {
        if(args.size() != 2) {
            utils::showMessage("Number of Arguments doesn't match\n");
            return;
        }

        std::string archive(args[0]);
        std::string targetStr(args[1]);

        if(this->archiveStream) {
            if(this->archiveStream->is_open()) this->archiveStream->close();
            delete this->archiveStream;
            this->archiveStream = nullptr;
        }

        this->archiveStream = new std::fstream(archive, READ);

        if(this->archiveStream->good()) {
            MetaData meta;

            while(this->archiveStream->good()) {
                *(this->archiveStream) >> meta;
                // check condition;
                FileBuffer buffer(meta.getFileSize());
                buffer.read(*(this->archiveStream), meta.getFileSize());
                if(meta.isTxtFile() && buffer.hasSubstr(targetStr)) {
                    utils::showMessage(meta.toString());
                }
                meta.reset();
            }
        }

        this->archiveStream->close();
    }
    
    void FileStorageEngineBase::extract(const std::vector<const char*>& args) {
        if(args.size() != 2) {
            utils::showMessage("Number of Arguments doesn't match\n");
            return;
        }

        std::string archive(args[0]);
        std::string targetPath(args[1]);
        std::string targetFileName = utils::getFileName(targetPath);

        if(this->archiveStream) {
            if(this->archiveStream->is_open()) this->archiveStream->close();
            delete this->archiveStream;
            this->archiveStream = nullptr;
        }

        this->archiveStream = new std::fstream(archive, READ);
        std::fstream targetStream(targetPath, WRITE);

        if(this->archiveStream->good() && targetStream.good()) {
            MetaData meta;

            while(this->archiveStream->good()) {
                *(this->archiveStream) >> meta;
                if(this->archiveStream->good()){
                    // check if file name matches
                    if(meta.getFileName() == targetFileName) {
                        FileBuffer buffer(meta.getFileSize());
                        buffer.read(*(this->archiveStream), meta.getFileSize());

                        // direct buffer content to stream output; targetStream can be used to extract to a file 
                        std::cout << buffer;
                        break;
                    } else {
                        this->archiveStream->seekg(meta.getFileSize() * sizeof(byte), std::fstream::cur);
                    }
                }
                meta.reset();
            }
        }

        this->archiveStream->flush();
        targetStream.flush();
        targetStream.close();
        this->archiveStream->close();
    }
    
    void FileStorageEngineBase::getVersion() {
        std::cout << APPNAME << " ";
        std::cout << "version " << VERSION << " ";
        std::cout << BUILDTIME << std::endl;
    }
}