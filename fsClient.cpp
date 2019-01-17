/**
 * Author: Hou Wang
 *
 * Description: This is the client program for FileStorageEngine
 * Specs: https://github.com/WoodyWangHou/FileStorage/blob/master/README.md
 */
#include <iostream>
#include <vector>
#include "CommandProcessor.hpp"

int main(int argc, char *argv[])
{
    // implement a concrete ArgParser::CommandBuilder
    using namespace filestorage;
    CommandProcessor processor;
    std::vector<const char*> args;

    for(unsigned i = 0; i < argc; i++){
        args.push_back(argv[i]);
    }

    processor.run(args);
}