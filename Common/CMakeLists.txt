cmake_minimum_required(VERSION 4.0)

set(LOCAL_SOURCES
        source/Vec2.cpp)

add_library(HH_Common ${LOCAL_SOURCES})

target_include_directories(HH_Common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)