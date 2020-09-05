project(config)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/inc ${CMAKE_CURRENT_SOURCE_DIR}/..)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src CONFIG_SOURCES)

add_library(config ${CONFIG_SOURCES})
add_dependencies(config nlohmann)
target_link_libraries(config nlohmann)

set_target_properties(config PROPERTIES LINKER_LANGUAGE CXX)

install(TARGETS config LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)
