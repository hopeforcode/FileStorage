/**
 * Author: Hou Wang
 *
 * Description: This file defines the file data block in archive
 */

#pragma once

#include <string>
#include <iostream>
#include <fstream>

namespace filestorage { namespace utils {
    inline void showMessage(std::string msg) {
        std::cout << msg;
    }

    inline int getFileSize(std::string filename) {
        std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
        return in.tellg(); 
    }

    inline std::string getFileExtension(std::string filePath) {
        std::size_t dotPos = filePath.rfind('.');

        if(dotPos != std::string::npos) {
            return filePath.substr(dotPos + 1);
        }
        return "";
    }

    inline std::string getFileName(std::string filePath, bool withExtension = true, char seperator = '/') {
        // Get last dot position
        std::size_t dotPos = filePath.rfind('.');
        std::size_t sepPos = filePath.rfind(seperator);
    
        if(sepPos != std::string::npos) {
            return filePath.substr(sepPos + 1, filePath.size() - (withExtension || dotPos != std::string::npos ? 1 : dotPos) );
        } else if(dotPos != std::string::npos) {
            return filePath;
        }

        return filePath;
    }

}}