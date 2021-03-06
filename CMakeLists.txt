CMAKE_MINIMUM_REQUIRED(VERSION 3.11)

PROJECT(Mandelbrot)

FIND_PACKAGE(SFML 2.5 COMPONENTS graphics audio REQUIRED)

FIND_PACKAGE(OpenMP)
if (OPENMP_FOUND)
    MESSAGE(STATUS "OpenMP found. Rendering will be faster.")

    SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
else()
    MESSAGE(WARNING "OpenMP NOT found. Rendering will be slower.")
endif()

ADD_SUBDIRECTORY(src)