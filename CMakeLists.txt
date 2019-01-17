set(CMAKE_VERSION "3.13.2")
set(PROJECT_NAME "FileStorage")
cmake_minimum_required(VERSION "${CMAKE_VERSION}")

project ("${PROJECT_NAME}")

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

# Set compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_library(FileStorageEngine FileStorageEngine.hpp FileStorageEngine.cpp)
add_library(CommandProcessor CommandProcessor.hpp CommandProcessor.cpp)
target_link_libraries(CommandProcessor FileStorageEngine)

file(GLOB HEADERS *.hpp)
source_group("Headers" FILES ${HEADERS})

add_executable(sfarchiver 
${HEADERS} 
fsClient.cpp
)

target_link_libraries(sfarchiver 
CommandProcessor
)