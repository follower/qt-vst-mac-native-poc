CMAKE_MINIMUM_REQUIRED(VERSION 2.8.9)

PROJECT(vster)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

FIND_PACKAGE(Qt5Core REQUIRED)


add_executable(vster main.cpp)

qt5_use_modules(vster Core)
