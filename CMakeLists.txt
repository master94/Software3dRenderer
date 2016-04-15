cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME Software3dRenderer)

project(${PROJECT_NAME})
add_definitions(--std=c++11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic -Wextra -Werror")
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Widgets REQUIRED)

add_executable(${PROJECT_NAME} main.cpp canvas.cpp renderer.cpp)
target_link_libraries(${PROJECT_NAME} Qt5::Widgets)
