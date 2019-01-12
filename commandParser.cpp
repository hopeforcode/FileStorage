/**
 * Author: Hou Wang
 *
 * Description: This is the argument parser for command line program (Implementation)
 */

#include "commandParser.hpp"
#include "Argument.hpp"

namespace filestorage {

    SfArchiverCommand::SfArchiverCommand(FileStorageEngineBase& r) {
        this->m_rece = std::shared_ptr<FileStorageEngineBase>(&r);
    }

    std::shared_ptr<FileStorageEngineBase> SfArchiverCommand::getFileStorageEngine() const {
        return this->m_rece;
    }

    void SfArchiverCommand::appendArg(Argument& arg) {
        this->arg = std::shared_ptr<Argument>(&arg);
    }

    std::shared_ptr<Argument> SfArchiverCommand::getArgument() const{
        return this->arg;
    }

    void AddCommand::exec() const {
        FileStorageEngineBase& receiver = *(this->getFileStorageEngine());
        Argument& arg = *(this->getArgument());
        receiver.add(arg);
    }

    void DelCommand::exec() const {
        FileStorageEngineBase& receiver = *(this->getFileStorageEngine());
        Argument& arg = *(this->getArgument());
        receiver.del(arg);
    }

    void ListCommand::exec() const {
        FileStorageEngineBase& receiver = *(this->getFileStorageEngine());
        Argument& arg = *(this->getArgument());
        receiver.list(arg);
    }

    void FindCommand::exec() const {
        FileStorageEngineBase& receiver = *(this->getFileStorageEngine());
        Argument& arg = *(this->getArgument());
        receiver.getProps(arg);
    }

    void ExtractCommand::exec() const {
        FileStorageEngineBase& receiver = *(this->getFileStorageEngine());
        Argument& arg = *(this->getArgument());
        receiver.extract(arg);
    }

    void VersionCommand::exec() const {
        FileStorageEngineBase& receiver = *(this->getFileStorageEngine());
        receiver.getVersion();
    }

    inline CommandParser::cmd_code CommandParser::hashString(std::string const& str) const {
        if(str == "add") return ADD;
        if(str == "del") return DELETE;
        if(str == "list") return LIST;
        if(str == "-l") return LIST;
        if(str == "find") return FIND;
        if(str == "extract") return EXTRACT;
        if(str == "version") return VERSION;
        if(str == "-v") return VERSION;
        return UNSUPPORTED;
    }

    void CommandParser::putArgs(std::string& arg){
        // remove blank
        std::string* str = new std::string;
        for(auto it = arg.begin(); it != arg.end(); ++it){
            if(*it == ' '){
                if(it != arg.begin()) {
                    // some string captured
                    this->args.add(*str);
                    str = new std::string;
                }else{
                    arg.erase(it);
                }
            }else {
                str->push_back(*it);
            }
        }
    }

    void CommandParser::putArgs(std::vector<std::string> args){
        for(std::string arg : args){
            if(!arg.empty()) {
                this->args.add(arg);
            }
        }
    }

    Command* CommandParser::parse(FileStorageEngineBase& fsEngine){
        Command* command;
        if(!this->args.isEmpty()) {
            std::string& cmd = this->args.poll();
            
            // implement cmd string parse
            switch(CommandParser::hashString(cmd)){
                case ADD:
                    command = new AddCommand(fsEngine);
                case DELETE:
                    command = new DelCommand(fsEngine);
                case LIST:
                    command = new ListCommand(fsEngine);
                case FIND:
                    command = new FindCommand(fsEngine);
                case EXTRACT:
                    command = new ExtractCommand(fsEngine);
                case VERSION:
                    command = new VersionCommand(fsEngine);
            } 
            
        }

        // throw exception and let error handling to print error
        return command;
    };
}