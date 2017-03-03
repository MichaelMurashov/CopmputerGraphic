cmake_minimum_required(VERSION 3.6)
project(Raytracing)

set(CMAKE_CXX_STANDARD 11)

include_directories("./include")

set(LIBRARY "lib_${MODULE}")

add_subdirectory(src)

#########################################################
# FIND GLEW
#########################################################

find_package(GLEW REQUIRED)

include_directories(${GLEW_INCLUDE_DIRS})
link_directories(${GLEW_LIBRARY_DIRS})
add_definitions(${GLEW_DEFINITIONS})

#########################################################
# FIND OPENGL
#########################################################

find_package(OpenGL REQUIRED)

include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})

#########################################################

set(SOURCE_FILES main.cpp)
add_executable(Raytracing ${SOURCE_FILES})

target_link_libraries(Raytracing ${OPENGL_gl_LIBRARY} ${GLFW_STATIC_LIBRARIES})

if (APPLE)
    target_link_libraries(Raytracing "-framework OpenGL")
endif()
