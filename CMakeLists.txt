cmake_minimum_required(VERSION 3.29)
project(StQueue)

set(CMAKE_CXX_STANDARD 23)

include_directories(.)

add_executable(StQueue
    main.cpp
    QueueList.hpp
    StackVector.hpp)
