cmake_minimum_required(VERSION 4.0)

cmake_dependent_option(IS_LINUX "Build system is Linux" ON "UNIX;NOT APPLE" OFF)

# Libraries
find_package(Vulkan REQUIRED)
set(LIBRARIES "glfw;Vulkan::Vulkan;imgui")

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
        ImguiComponents/SameLine.cpp
        ImguiComponents/Window.cpp
        Test/TestVulkanData.cpp
        Test/TestWindow.cpp
)

set(PUBLIC_HEADERS
        Window/HomeworkWindow.h
        Window/Window.h
        Window/WindowHandler.h
        ImguiComponents/ImguiComponent.h
        ImguiComponents/MenuBar.h
        ImguiComponents/MenuTab.h
        ImguiComponents/MenuItem.h
        ImguiComponents/Button.h
        ImguiComponents/Textfield.h
        ImguiComponents/RadioButton.h
        ImguiComponents/NumberField.h
        ImguiComponents/ImGuiID.h
        ImguiComponents/IntSlider.h
        ImguiComponents/Checkbox.h
        ImguiComponents/ComboBox.h
        ImguiComponents/ComboItem.h
        ImguiComponents/Label.h
        ImguiComponents/SeparatorLine.h
        ImguiComponents/CollapsableHeader.h
        ImguiComponents/TreeNode.h
        ImguiComponents/SameLine.h
        ImguiComponents/Window.h
        Test/TestVulkanData.h
        Test/TestWindow.h
)

set(PRIVATE_HEADERS
        GUIIncludes.h
        Test/TestFunctions.h
)

if (IS_LINUX)
    find_package(X11 REQUIRED)
    include_directories(${X11_INCLUDE_DIR})
    link_directories(${X11_LIBRARIES})
endif ()

add_library(HH_GUI
        ${LOCAL_SOURCES}
)

target_link_libraries(HH_GUI
        HH_Common
        ${LIBRARIES}
)

if (IS_LINUX)
    target_link_libraries(HH_GUI ${X11_LIBRARIES})
endif ()
