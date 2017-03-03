cmake_minimum_required(VERSION 3.6)
project(Raytracing)

set(CMAKE_CXX_STANDARD 11)

include_directories("./include")

set(LIBRARY "lib_${MODULE}")

add_subdirectory(src)

#########################################################
# FIND GLUT
#########################################################

find_package(GLUT REQUIRED)

include_directories(${GLUT_INCLUDE_DIRS})
link_directories(${GLUT_LIBRARY_DIRS})
add_definitions(${GLUT_DEFINITIONS})

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

target_link_libraries(Raytracing ${OPENGL_gl_LIBRARY} ${GLUT_glut_LIBRARY})
