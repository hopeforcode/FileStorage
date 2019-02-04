/**
 * Author: Hou Wang
 *
 * Description: This is the argument parser for command line program
 * User Command Pattern to define a extensible command line application
 * Parse command line arguments to perform corresponding actions
 * 
 * Application: sfarchiver
 * Association: file storage engine, command parser
 * 
 */

#pragma once

#include <unordered_map>
#include <string>
#include <vector>

namespace filestorage {

    class Command {
        private:
            std::string mKeyword;
        public:
            Command(const std::string& aKeyword) : mKeyword(aKeyword) {};
            virtual Command& operator() (const std::vector<const char*>& keyword){
                // to be overloadded - for execution
                return *this;
            }

            std::string& getKeyword(){
                return this->mKeyword;
            }
    };

    class AddCommand : public Command {
        public:
            AddCommand(const std::string& str) : Command(str) {};
            Command& operator() (const std::vector<const char*>& args);
    };

    class DelCommand : public Command {
        public:
            DelCommand(const std::string& str) : Command(str) {};
            Command& operator() (const std::vector<const char*>& args);
    };

    class ListCommand : public Command {
        public:
            ListCommand(const std::string& str) : Command(str) {};
            Command& operator() (const std::vector<const char*>& args);
    };

    class FindCommand : public Command {
        public:
            FindCommand(const std::string& str) : Command(str) {};
            Command& operator() (const std::vector<const char*>& args);
    };

    class ExtractCommand : public Command {
        public:
            ExtractCommand(const std::string& str) : Command(str) {};
            Command& operator() (const std::vector<const char*>& args);
    };

    class VersionCommand : public Command {
        public:
            VersionCommand(const std::string& str) : Command(str) {};
            Command& operator() (const std::vector<const char*>& args);
    };

    // Client class to invoke commands
    class CommandProcessor{
        private:
            std::unordered_map<std::string, Command*> mCommands;
        public: 
            CommandProcessor() {
                addCommand(new AddCommand("add"));
                addCommand(new DelCommand("del"));
                addCommand(new ListCommand("list"));
                addCommand(new FindCommand("find"));
                addCommand(new ExtractCommand("extract"));
                addCommand(new VersionCommand("version"));
            };

            void addCommand(Command* cmd){
                std::string aKeyword = cmd->getKeyword();
                if(this->mCommands.find(aKeyword) == this->mCommands.end()){
                    // no conflict commands
                    mCommands[cmd->getKeyword()] = cmd;
                }
            }

            void run(std::vector<const char*>& args) const;
    };
}