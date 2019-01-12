/**
 * Author: Hou Wang
 * 
 * Application: sfarchiver
 * Association: file storage engine, command parser
 * 
 */

#include "Argument.hpp"
#include <string>

namespace filestorage {
    void Argument::add(std::string& arg) {
        this->m_args.push_back(arg);
    }

    std::string& Argument::poll() {
        if(this->isEmpty()){
            std::string res;
            return res;
        }

        std::string& res = this->m_args.front();
        this->m_args.erase(this->m_args.begin());
        return res;
    }

    bool Argument::isEmpty() {
        return this->m_args.empty();
    }
}