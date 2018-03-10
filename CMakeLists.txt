cmake_minimum_required(VERSION 2.8)
project(ADNS_5050)
cmake_policy(SET CMP0015 NEW)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)
set(ADNS_5050 ${PROJECT_SOURCE_DIR}/src/ADNS_5050.cpp)

set(GL_LIBS GLESv2 EGL)

include_directories(${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS})

add_definitions(-L${PROJECT_SOURCE_DIR}/lib/wiringPi/wiringPi.h -lwiringPi)

add_subdirectory(examples/product_id)
add_subdirectory(examples/test_read_time)