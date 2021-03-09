PROJECT(Mandelbrot)

ADD_EXECUTABLE(mandelbrot ./main.cpp)

TARGET_LINK_LIBRARIES(mandelbrot sfml-graphics sfml-audio)
SET_PROPERTY(TARGET mandelbrot PROPERTY CXX_STANDARD 14)