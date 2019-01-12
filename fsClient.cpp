/**
 * Author: Hou Wang
 *
 * Description: This is the client program for FileStorageEngine
 * Specs: https://github.com/WoodyWangHou/FileStorage/blob/master/README.md
 */

#include <iostream>
#include "commandParser.hpp"
#include "FileStorageEngine.hpp"

int main(int argc, char *argv[])
{
    // implement a concrete ArgParser::CommandBuilder
    using namespace filestorage;
    FileStorageEngineBase fsEngine;
    CommandParser parser;

    for(int i = 0; i < argc; ++i){
        std::string str(argv[i]);
        parser.putArgs(str);
    }

    Command* command = parser.parse(fsEngine);
    command->exec();
}