cmake_minimum_required(VERSION 3.10)
project(untitled)

set(CMAKE_CXX_STANDARD 14)
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lboost_graph -lboost_timer")

add_executable(main main.cpp)
add_executable(generate_graph generate_graph.cpp)
add_executable(tarjan_bgl example_tarjan.cpp)
add_executable(tarjan my_tarjan.cpp)
add_executable(nuutila my_nuutila.cpp)
add_executable(pearce my_pearce.cpp)
