project(file)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/inc)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src FILE_SOURCES)

add_library(file ${FILE_SOURCES})