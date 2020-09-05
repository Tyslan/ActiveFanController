cmake_minimum_required(VERSION 3.10)

# set the project name
project(ActiveFanControlProject VERSION 0.1)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(lib)
add_subdirectory(app)
