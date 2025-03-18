cmake_minimum_required(VERSION 3.29)
project(StQueue)

set(CMAKE_CXX_STANDARD 20)

add_executable(StQueue main.cpp
        StackVector.hpp
        QueueList.hpp
)
