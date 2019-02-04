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

    class FileStorageEngineBase {
        private:
            static FileStorageEngineBase* mInstance;

        protected:
            FileStorageEngineBase();
            std::fstream* file;

        public:
            static FileStorageEngineBase* getInstance();
            void add(const std::vector<const char*>& args); 
            void del(const std::vector<const char*>& args);
            void list(const std::vector<const char*>& args);
            void getProps(const std::vector<const char*>& args);
            void extract(const std::vector<const char*>& args);
            void getVersion();

            ~FileStorageEngineBase() {
                if(file) {
                    if(file->is_open()) {
                        file->close();
                    }
                    delete file;
                    file = nullptr;
                }
            }
    };
}