cmake_minimum_required(VERSION 3.6)
project(RLC)

set(CMAKE_CXX_STANDARD 11)

### find OpenCV ###
find_package(OpenCV REQUIRED)
message(STATUS "OpenCV library status:")
message(STATUS "    version: ${OpenCV_VERSION}")
message(STATUS "    libraries: ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")

set(SOURCE_FILES main.cpp)
add_executable(RLC ${SOURCE_FILES})

target_link_libraries(RLC ${OpenCV_LIBS})
