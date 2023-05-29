# CMakeLists.txt for Imgui

# Add all Imgui source files to the IMGUI_SRCS variable
set(IMGUI_SRCS
    imgui.cpp
    imgui_draw.cpp
    imgui_widgets.cpp
    imgui_tables.cpp
    imgui_demo.cpp
    backends/imgui_impl_glfw.cpp  # (your chosen backend)
    backends/imgui_impl_opengl3.cpp)

# Define the Imgui library target
add_library(imgui ${IMGUI_SRCS})

# Set the include directories for the Imgui library target
target_include_directories(imgui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})