cmake_minimum_required(VERSION 3.28)
project(wfinder)

set(CMAKE_CXX_STANDARD 17)

add_executable(wfinder main.cpp WordSegmenter.cpp AhoCorasick.hpp WordsFinder.cpp)
