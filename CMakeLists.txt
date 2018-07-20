cmake_minimum_required(VERSION 3.10)
project(untitled)

#set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lboost_graph -lboost_timer -pg")

set(CMAKE_CXX_STANDARD 11)

FIND_PACKAGE( Boost 1.65 COMPONENTS graph timer REQUIRED )
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )

add_executable(main main.cpp)
add_executable(test_stdin test_from_stdin.cpp)
add_executable(generate_graph generate_graph.cpp)
add_executable(tarjan main_tarjan.cpp)
add_executable(nuutila main_nuutila.cpp)
add_executable(pearce main_pearce.cpp)
add_executable(pearce_nr main_pearce_not_recursive.cpp)
add_executable(transitive_closure main_transitive_closure.cpp)

TARGET_LINK_LIBRARIES(main ${Boost_LIBRARIES} )
TARGET_LINK_LIBRARIES(generate_graph ${Boost_LIBRARIES} )
TARGET_LINK_LIBRARIES(tarjan ${Boost_LIBRARIES} )
TARGET_LINK_LIBRARIES(nuutila ${Boost_LIBRARIES} )
TARGET_LINK_LIBRARIES(pearce ${Boost_LIBRARIES} )
TARGET_LINK_LIBRARIES(pearce_nr ${Boost_LIBRARIES} )
TARGET_LINK_LIBRARIES(test_stdin ${Boost_LIBRARIES} )
TARGET_LINK_LIBRARIES(transitive_closure ${Boost_LIBRARIES} )

