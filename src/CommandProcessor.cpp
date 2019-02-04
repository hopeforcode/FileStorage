/**
 * Author: Hou Wang
 *
 * Description: This is the argument parser for command line program (Implementation)
 */
#include <iostream>
#include "CommandProcessor.hpp"
#include "FileStorageEngine.hpp"

namespace filestorage {

    //TODO: Implement all commands
    Command& AddCommand::operator() (const std::vector<const char*>& args) {
        FileStorageEngineBase* fsEngine = FileStorageEngineBase::getInstance();
        fsEngine->add(args);
        return *this;
    }

    Command& DelCommand::operator() (const std::vector<const char*>& args) {
        FileStorageEngineBase* fsEngine = FileStorageEngineBase::getInstance();
        fsEngine->del(args);
        return *this;
    }

    Command& ListCommand::operator() (const std::vector<const char*>& args) {
        FileStorageEngineBase* fsEngine = FileStorageEngineBase::getInstance();
        fsEngine->list(args);
        return *this;
    }

    Command& FindCommand::operator() (const std::vector<const char*>& args) {
        FileStorageEngineBase* fsEngine = FileStorageEngineBase::getInstance();
        fsEngine->getProps(args);
        return *this;
    }

    Command& ExtractCommand::operator() (const std::vector<const char*>& args) {
        FileStorageEngineBase* fsEngine = FileStorageEngineBase::getInstance();
        fsEngine->extract(args);
        return *this;
    }

    Command& VersionCommand::operator() (const std::vector<const char*>& args) {
        FileStorageEngineBase* fsEngine = FileStorageEngineBase::getInstance();
        fsEngine->getVersion();
        return *this;
    }

    void CommandProcessor::run(std::vector<const char*>& args) const {
        if(!args.empty()){
            const std::string& cmd= args[1];
            args.erase(args.begin(), args.begin() + 2);
            if(mCommands.find(cmd) != mCommands.end()){
                // found matching commands
                (*(mCommands.at(cmd)))(args);
            }
        }
    }
}