cmake_minimum_required(VERSION 3.29)
project(PolynomialInterpolation)

set(CMAKE_CXX_STANDARD 20)

add_executable(PolynomialInterpolation
        hermit.cpp
        lagranzh.cpp
        functions.cpp
        functions.h
        main.cpp
)
