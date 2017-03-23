cmake_minimum_required(VERSION 3.6)
project(noise)

set(CMAKE_CXX_STANDARD 11)
set(LIBRARY "_noise")

include_directories("./include")

add_subdirectory(src)

### find OpenCV ###
find_package(OpenCV REQUIRED)
message(STATUS "OpenCV library status:")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")

set(SOURCE_FILES main.cpp)
add_executable(noise ${SOURCE_FILES})

target_link_libraries(noise ${OpenCV_LIBS})
