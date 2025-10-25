cmake_minimum_required(VERSION 4.0)

# Libraries
find_package(glfw3 3.4 REQUIRED)
find_package(Vulkan REQUIRED)
set(LIBRARIES "glfw;Vulkan::Vulkan")

set(LOCAL_SOURCES
        Window/HomeworkWindow.cpp
        Window/Window.cpp
        Window/WindowHandler.cpp
        ImguiComponents/ImguiComponent.cpp
        ImguiComponents/MenuBar.cpp
        ImguiComponents/MenuTab.cpp
        ImguiComponents/MenuItem.cpp
        ImguiComponents/Button.cpp
        ImguiComponents/Textfield.cpp
        ImguiComponents/RadioButton.cpp
        ImguiComponents/NumberField.cpp
        ImguiComponents/ImGuiID.cpp
        ImguiComponents/IntSlider.cpp
        ImguiComponents/Checkbox.cpp
        ImguiComponents/ComboBox.cpp
        ImguiComponents/ComboItem.cpp
        ImguiComponents/Label.cpp
        ImguiComponents/SeparatorLine.cpp
        ImguiComponents/CollapsableHeader.cpp
        ImguiComponents/TreeNode.cpp
)

# Dear ImGui
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

# Linux
find_package(X11 REQUIRED)
include_directories(${X11_INCLUDE_DIR})
link_directories(${X11_LIBRARIES})

add_library(HH_GUI
        ${LOCAL_SOURCES}
        ${IMGUI_SOURCES}
)

target_link_libraries(HH_GUI
        HH_Common
        ${LIBRARIES}
)
# Linux
target_link_libraries(HH_GUI ${X11_LIBRARIES})