cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME ModelsLoader)
project(${PROJECT_NAME})
include_directories(${CMAKE_SOURCE_DIR})

add_library(${PROJECT_NAME} STATIC ObjModelLoader.cpp)
