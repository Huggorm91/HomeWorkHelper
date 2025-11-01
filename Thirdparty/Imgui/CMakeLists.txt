cmake_minimum_required(VERSION 4.0)

set(IMGUI_DIR ${PROJECT_SOURCE_DIR}/Thirdparty/Imgui)
set(IMGUI_INCLUDES ${IMGUI_DIR} ${IMGUI_DIR}/backends)
set(IMGUI_SOURCES
        ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
        ${IMGUI_DIR}/backends/imgui_impl_vulkan.cpp
        ${IMGUI_DIR}/imgui.cpp
        ${IMGUI_DIR}/imgui_draw.cpp
        ${IMGUI_DIR}/imgui_tables.cpp
        ${IMGUI_DIR}/imgui_widgets.cpp
)
include_directories(${IMGUI_INCLUDES})

add_library(imgui
        ${IMGUI_SOURCES}
)

target_include_directories(imgui
        PUBLIC ${IMGUI_INCLUDES}
)