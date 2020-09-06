project(afc)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../lib)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src ActiveFanController_SOURCES)

add_executable(afc fan_controller.cpp)

add_dependencies(afc config thermal fan pwm file)
target_link_libraries(afc config thermal fan pwm file)

install(TARGETS afc RUNTIME DESTINATION bin ARCHIVE DESTINATION bin)