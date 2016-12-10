cmake_minimum_required(VERSION 3.5)

project (abouda-llvm)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

add_executable(abouda-llvm main.cpp)

include_directories(include)

add_subdirectory(src)
add_subdirectory(test)

target_link_libraries(abouda-llvm src)
