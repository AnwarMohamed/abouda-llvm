cmake_minimum_required(VERSION 3.5)

add_definitions(-std=c++11)

set(SRC_FILES
    Lexer.cpp
    Token.cpp  
    Dfa.cpp
)

add_library(lexer STATIC ${SRC_FILES})
