cmake_minimum_required(VERSION 3.1)

project(Mandelbrot)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

find_package(OpenMP)
if (OPENMP_FOUND)
    message(STATUS "OpenMP found. Rendering will be faster.")

    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
else()
    message(WARNING "OpenMP NOT found. Rendering will be slower.")
endif()

add_executable(mandelbrot ./src/main.cpp)

target_link_libraries(mandelbrot sfml-graphics sfml-audio)