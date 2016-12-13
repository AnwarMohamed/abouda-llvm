cmake_minimum_required(VERSION 3.5)

add_definitions(-std=c++11)

set(SRC_FILES
   BaseParser.cpp
)

add_library(parser STATIC ${SRC_FILES})
