cmake_minimum_required(VERSION 3.17)
project(DA_PROJ2)

set(CMAKE_CXX_STANDARD 11)

add_executable(project include/Graph.h source/Graph.cpp include/VertexEdge.h source/VertexEdge.cpp)