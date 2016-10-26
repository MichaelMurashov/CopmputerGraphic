cmake_minimum_required(VERSION 3.6)
project(opengl)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories("./include")

set(MODULE "${PROJECT_NAME}")
set(LIBRARY "lib_${MODULE}")
set(APPLICATION "app_${MODULE}")

add_subdirectory(src)
add_subdirectory(app)
