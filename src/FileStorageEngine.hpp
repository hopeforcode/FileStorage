/**
 * Author: Hou Wang
 * 
 * Application: sfarchiver
 * Association: file storage engine, command parser
 * 
 */
#pragma once

#include <vector>
#include <fstream>

namespace filestorage{

    extern const char *VERSION;
    extern const char *APPNAME;
    extern const char *BUILDTIME;
    extern const std::fstream::openmode APPEND;
    extern const std::fstream::openmode READ;
    extern const std::fstream::openmode WRITE;

    class FileStorageEngineBase {
        private:
            static FileStorageEngineBase* mInstance;

        protected:
            FileStorageEngineBase();
            std::fstream* archiveStream;

        public:
            static FileStorageEngineBase* getInstance();
            void add(const std::vector<const char*>& args); 
            void del(const std::vector<const char*>& args);
            void list(const std::vector<const char*>& args);
            void getProps(const std::vector<const char*>& args);
            void extract(const std::vector<const char*>& args);
            void getVersion();

            ~FileStorageEngineBase() {
                if(archiveStream) {
                    if(archiveStream->is_open()) {
                        archiveStream->close();
                    }
                    delete archiveStream;
                    archiveStream = nullptr;
                }
            }
    };
}