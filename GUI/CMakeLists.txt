cmake_minimum_required(VERSION 4.0)

# Libraries
find_package(glfw3 3.4 REQUIRED)
find_package(Vulkan REQUIRED)
set(LIBRARIES "glfw;Vulkan::Vulkan")

set(LOCAL_SOURCES
        source/HomeworkWindow.cpp
        source/Window.cpp
        source/WindowHandler.cpp
)

# Dear ImGui
set(IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../Thirdparty/Imgui)
set(IMGUI_INCLUDES ${IMGUI_DIR} ${IMGUI_DIR}/backends)
set(IMGUI_SOURCES
        ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
        ${IMGUI_DIR}/backends/imgui_impl_vulkan.cpp
        ${IMGUI_DIR}/imgui.cpp
        ${IMGUI_DIR}/imgui_draw.cpp
        ${IMGUI_DIR}/imgui_tables.cpp
        ${IMGUI_DIR}/imgui_widgets.cpp
        # TODO: Remove this
        ${IMGUI_DIR}/imgui_demo.cpp
)
include_directories(${IMGUI_INCLUDES})

# Linux
find_package(X11 REQUIRED)
include_directories(${X11_INCLUDE_DIR})
link_directories(${X11_LIBRARIES})

add_library(HH_GUI
        ${LOCAL_SOURCES}
        ${IMGUI_SOURCES}
)

target_include_directories(HH_GUI
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
        PUBLIC ${IMGUI_INCLUDES}
)

target_link_libraries(HH_GUI
        ${LIBRARIES}
)
# Linux
target_link_libraries(HH_GUI ${X11_LIBRARIES})