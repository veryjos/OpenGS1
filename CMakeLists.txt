cmake_minimum_required(VERSION 3.3)
project(gs1parse)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT MSVC)
  #set(CMAKE_CXX_COMPILER clang++)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)

add_definitions(-D_CRT_SECURE_NO_WARNINGS)
add_definitions(-D_SCL_SECURE_NO_WARNINGS)

include_directories(include)

add_subdirectory(src/gs1common)
add_subdirectory(src/gs1parse)
add_subdirectory(src/gs1test)
add_subdirectory(src/gs1compiler)
add_subdirectory(src/gs1vm)