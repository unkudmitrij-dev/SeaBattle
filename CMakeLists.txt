cmake_minimum_required(VERSION 3.31)
project(SeaBattle)

set(CMAKE_CXX_STANDARD 26)

add_executable(SeaBattle main.cpp
        GameTypes.h
        GameTypes.cpp
        Ship.cpp
        Ship.h
        Board.cpp
        Board.h
        FleetPlacement.cpp
        FleetPlacement.h)
