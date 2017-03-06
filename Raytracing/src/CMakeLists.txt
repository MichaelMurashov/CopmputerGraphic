set(target ${LIBRARY})

file(GLOB hrcs "${CMAKE_HOME_DIRECTORY}/include/*.h")
file(GLOB srcs "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)

#include_directories(${OPENGL_INCLUDE_DIR} ${GLEW_INCLUDE_DIRS})

add_library(${target} STATIC ${srcs} ${hrcs})

target_link_libraries(${target} ${OPENGL_gl_LIBRARY} ${GLEW_LIBRARIES} glfw)