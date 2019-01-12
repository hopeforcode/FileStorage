/**
 * Author: Hou Wang
 * 
 * Application: sfarchiver
 * Association: file storage engine, command parser
 * 
 */

#pragma once
#include <vector>

namespace filestorage {
    class Argument {
        private:
            std::vector<std::string> m_args;
        public:
            void add(std::string& arg);
            std::string& poll();
            bool isEmpty();
    }; 
}