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

#include <vector>
#include <string>
#include <memory>
#include "FileStorageEngine.hpp"
#include "Argument.hpp"

namespace filestorage {

    class Command {
        public:
            virtual void exec() const = 0;
    };
    
    class SfArchiverCommand : public Command {
        private:
            std::shared_ptr<FileStorageEngineBase> m_rece;
            std::shared_ptr<Argument> arg;

        public:
            SfArchiverCommand(FileStorageEngineBase& r);
            std::shared_ptr<FileStorageEngineBase> getFileStorageEngine() const;
            std::shared_ptr<Argument> getArgument() const;
            void appendArg(Argument& arg);
    };

    class AddCommand : public SfArchiverCommand {
        public:
            AddCommand(FileStorageEngineBase& r) : SfArchiverCommand(r){};
            void exec() const;
    };

    class DelCommand : public SfArchiverCommand {
        public:
            DelCommand(FileStorageEngineBase& r) : SfArchiverCommand(r){};
            void exec() const;
    };

    class ListCommand : public SfArchiverCommand {
        public:
            ListCommand(FileStorageEngineBase& r) : SfArchiverCommand(r){};
            void exec() const;
    };

    class FindCommand : public SfArchiverCommand {
        public:
            FindCommand(FileStorageEngineBase& r) : SfArchiverCommand(r){};
            void exec() const;
    };

    class ExtractCommand : public SfArchiverCommand {
        public:
            ExtractCommand(FileStorageEngineBase& r) : SfArchiverCommand(r){};
            void exec() const;
    };

    class VersionCommand : public SfArchiverCommand {
        public:
            VersionCommand(FileStorageEngineBase& r) : SfArchiverCommand(r){};
            void exec() const;
    };

    // Client class to invoke commands
    class CommandParser{
        enum cmd_code{
            ADD,
            DELETE,
            LIST,
            FIND,
            EXTRACT,
            VERSION,
            UNSUPPORTED
        };

        private:
            Argument args;

            cmd_code hashString(std::string const& str) const;
        public: 
            void putArgs(std::string& arg);
            void putArgs(std::vector<std::string> args);
            Command* parse(FileStorageEngineBase& fsEngine); // generate command
    };
}