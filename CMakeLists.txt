cmake_minimum_required(VERSION 3.14)
project(test_task)

set(CMAKE_CXX_STANDARD 14)

add_executable(test_task main.cpp src/PairArray.h src/PairMap.h src/AVLTree.h src/Container.h)