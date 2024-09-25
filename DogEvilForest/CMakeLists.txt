cmake_minimum_required(VERSION 3.29)
project(DogEvilForest)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(DogEvilForest
    Board.cpp
    Board.hpp
    mainGame.cpp
        Dog.cpp
        Dog.hpp)
