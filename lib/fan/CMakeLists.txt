project(fan)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/inc ${CMAKE_CURRENT_SOURCE_DIR}/..)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src FAN_SOURCES)

add_library(fan ${FAN_SOURCES})

set_target_properties(fan PROPERTIES LINKER_LANGUAGE CXX)
install(TARGETS fan LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)