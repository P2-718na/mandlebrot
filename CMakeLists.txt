cmake_minimum_required(VERSION 3.1)

project(Mandelbrot)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
add_executable(mandelbrot ./src/main.cpp)

target_link_libraries(mandelbrot sfml-graphics sfml-audio)