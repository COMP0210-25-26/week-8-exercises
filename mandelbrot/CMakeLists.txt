cmake_minimum_required(VERSION 3.13)
project(mandelbrot)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(mandelbrot main.cpp)

find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    target_link_libraries(mandelbrot PUBLIC OpenMP::OpenMP_CXX)
endif()
