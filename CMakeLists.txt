cmake_minimum_required(VERSION 3.23)
project(Centrality)

set(CMAKE_CXX_STANDARD 14)

include_directories(C:\\CplusplusLibs\\rapidjson-1.1.0\\include)
# Set the path to the Boost Library
set(BOOST_ROOT C:\\CplusplusLibs\\boost_1_81_0)

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

add_executable(Centrality main.cpp)
target_link_libraries(Centrality ${Boost_LIBRARIES})
target_link_libraries(Centrality ${OTHER_LIBRARIES})

