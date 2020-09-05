project(pwm)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/inc ${CMAKE_CURRENT_SOURCE_DIR}/..)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src PWM_SOURCES)

add_library(pwm ${PWM_SOURCES})
add_dependencies(pwm file)
target_link_libraries(pwm file)

set_target_properties(pwm PROPERTIES LINKER_LANGUAGE CXX)
install(TARGETS pwm LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)