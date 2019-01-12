/**
 * Author: Hou Wang
 * 
 * Application: sfarchiver
 * Association: file storage engine, command parser
 * 
 */
#pragma once

#include "commandParser.hpp"
#include "Argument.hpp"

namespace filestorage{
    class FileStorageEngineBase {
        public:
            void add(Argument& arg); 
            void del(Argument& arg);
            void list(Argument& arg);
            void getProps(Argument& arg);
            void extract(Argument& arg);
            void getVersion();
    };
}