cmake_minimum_required(VERSION 3.13.2)

project (FileStorage)

add_library(commandParser.hpp commandParser.cpp)
add_library(Argument.hpp Argument.cpp)
add_library(FileStorageEngine.hpp FileStorageEngine.cpp)
add_executable(sfarchiver fsClient.cpp)