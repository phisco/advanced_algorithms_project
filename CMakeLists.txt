cmake_minimum_required(VERSION 3.10)
project(untitled)

set(CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lboost_graph")

add_executable(main main.cpp)
add_executable(generate_graph generate_graph.cpp)
add_executable(tarjan example_tarjan.cpp)
add_executable(my_tarjan my_tarjan.cpp)
