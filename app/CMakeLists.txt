project(ActiveFanController)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../lib)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src ActiveFanController_SOURCES)

add_executable(ActiveFanController fan_controller.cpp)

add_dependencies(ActiveFanController config thermal fan pwm)
target_link_libraries(ActiveFanController config thermal fan pwm)

install(TARGETS ActiveFanController RUNTIME DESTINATION bin ARCHIVE DESTINATION bin)