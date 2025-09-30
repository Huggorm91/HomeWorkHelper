cmake_minimum_required(VERSION 4.0)

find_package(PkgConfig REQUIRED)
pkg_check_modules(gtkmm REQUIRED IMPORTED_TARGET gtkmm-4.0 glibmm-2.68)

add_library(HH_GUI source/MainWindow.cpp)

target_include_directories(HH_GUI PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(HH_GUI PUBLIC PkgConfig::gtkmm)