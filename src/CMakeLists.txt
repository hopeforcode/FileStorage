add_library(ArchiveFileBuffer ArchiveFileBuffer.hpp ArchiveFileBuffer.cpp)
add_library(ArchiveMetadata ArchiveMetadata.hpp ArchiveMetadata.cpp)
add_library(FileStorageEngine FileStorageEngine.hpp FileStorageEngine.cpp)
add_library(CommandProcessor CommandProcessor.hpp CommandProcessor.cpp)

target_link_libraries(FileStorageEngine ArchiveFileBuffer ArchiveMetadata)
target_link_libraries(CommandProcessor FileStorageEngine)

set(HEADERS CommandProcessor.hpp)

add_executable(sfarchiver 
${HEADERS} 
fsClient.cpp
)

target_link_libraries(sfarchiver 
CommandProcessor
)