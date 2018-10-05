cmake_minimum_required(VERSION 3.10)
project(Grafo)

set(CMAKE_CXX_STANDARD 11)

add_executable(Grafo main.cpp node.h read.h graph.h edge.h)
