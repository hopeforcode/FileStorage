set(CMAKE_VERSION "3.5.1")
set(PROJECT_NAME "FileStorage")
cmake_minimum_required(VERSION "${CMAKE_VERSION}")

project ("${PROJECT_NAME}")

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

# Set compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_subdirectory(src)