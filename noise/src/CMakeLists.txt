set(target ${LIBRARY})

file(GLOB hrcs "${CMAKE_HOME_DIRECTORY}/include/*.h")
file(GLOB srcs "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

find_package(OpenCV REQUIRED)

add_library(${target} STATIC ${srcs} ${hrcs})

target_link_libraries(${target} ${OpenCV_LIBS})
