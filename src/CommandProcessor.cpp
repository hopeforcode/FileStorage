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
        fsEngine->add();
        return *this;
    }

    Command& DelCommand::operator() (const std::vector<const char*>& args) {
        FileStorageEngineBase* fsEngine = FileStorageEngineBase::getInstance();
        fsEngine->del();
        return *this;
    }

    Command& ListCommand::operator() (const std::vector<const char*>& args) {
        FileStorageEngineBase* fsEngine = FileStorageEngineBase::getInstance();
        fsEngine->list();
        return *this;
    }

    Command& FindCommand::operator() (const std::vector<const char*>& args) {
        FileStorageEngineBase* fsEngine = FileStorageEngineBase::getInstance();
        fsEngine->getProps();
        return *this;
    }

    Command& ExtractCommand::operator() (const std::vector<const char*>& args) {
        FileStorageEngineBase* fsEngine = FileStorageEngineBase::getInstance();
        fsEngine->extract();
        return *this;
    }

    Command& VersionCommand::operator() (const std::vector<const char*>& args) {
        FileStorageEngineBase* fsEngine = FileStorageEngineBase::getInstance();
        fsEngine->getVersion();
        return *this;
    }

    void CommandProcessor::run(const std::vector<const char*>& args) const {
        if(!args.empty()){
            const std::string& cmd= args[1];
            if(mCommands.find(cmd) != mCommands.end()){
                // found matching commands
                (*(mCommands.at(cmd)))(args);
            }
        }
    }
}