project(thermal)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/inc ${CMAKE_CURRENT_SOURCE_DIR}/..)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src THERMAL_SOURCES)

add_library(thermal ${THERMAL_SOURCES})
add_dependencies(thermal file)
target_link_libraries(thermal file)

set_target_properties(thermal PROPERTIES LINKER_LANGUAGE CXX)
install(TARGETS thermal LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)