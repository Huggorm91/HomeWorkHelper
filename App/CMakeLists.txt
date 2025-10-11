cmake_minimum_required(VERSION 4.0)

add_executable(${CMAKE_PROJECT_NAME} source/main.cpp)
target_link_libraries(${CMAKE_PROJECT_NAME} HH_GUI)