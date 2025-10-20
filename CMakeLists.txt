cmake_minimum_required(VERSION 4.0)
project(HomeworkHelper)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/_bin/${CMAKE_BUILD_TYPE})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY  ${PROJECT_SOURCE_DIR}/_lib/${CMAKE_BUILD_TYPE})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY  ${PROJECT_SOURCE_DIR}/_lib/${CMAKE_BUILD_TYPE})
set(CMAKE_CFG_INTDIR ${PROJECT_SOURCE_DIR}/_temp/${CMAKE_BUILD_TYPE})

add_subdirectory(Common)    # Common Utilities library
add_subdirectory(GUI)       # Gui library
add_subdirectory(App)       # App executable
