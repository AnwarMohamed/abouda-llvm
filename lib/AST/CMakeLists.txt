cmake_minimum_required(VERSION 3.5)

add_definitions(-std=c++11)

set(SRC_FILES
   BaseAST.cpp
)

add_library(ast STATIC ${SRC_FILES})
