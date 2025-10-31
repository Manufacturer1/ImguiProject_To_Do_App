# CMakeList.txt : CMake project for ImguiProject, include source and define
# project specific logic here.

cmake_minimum_required(VERSION 3.12)

project(ImguiProject)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add source to this project's executable.
add_executable(ImguiProject 
    "ImguiProject.cpp"  
    "UseImgui.h" 
    "UseImgui.cpp" 
    "ManageItems.h" 
    "ImGuiStyles.h"  
    "loadTexture.h"
)

# Copy Fonts folder
add_custom_command(TARGET ImguiProject POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/ImguiProject/Fonts"
        $<TARGET_FILE_DIR:ImguiProject>/Fonts
)

# Copy icons folder
add_custom_command(TARGET ImguiProject POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/ImguiProject/icons"
        $<TARGET_FILE_DIR:ImguiProject>/icons
)

# Find and link packages - vcpkg toolchain will locate them automatically
find_package(glad CONFIG REQUIRED)	
target_link_libraries(ImguiProject PRIVATE glad::glad)

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(ImguiProject PRIVATE glfw)

find_package(imgui CONFIG REQUIRED)
target_link_libraries(ImguiProject PRIVATE imgui::imgui)

find_package(Stb REQUIRED)
target_include_directories(ImguiProject PRIVATE ${Stb_INCLUDE_DIR})

find_package(gl3w CONFIG REQUIRED)
target_link_libraries(ImguiProject PRIVATE unofficial::gl3w::gl3w)

# Copy DLLs on Windows (vcpkg handles this automatically in most cases)
if(WIN32)
    # Copy gl3w.dll if it exists
    add_custom_command(TARGET ImguiProject POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_RUNTIME_DLLS:ImguiProject>
            $<TARGET_FILE_DIR:ImguiProject>
        COMMAND_EXPAND_LISTS
    )
endif()

# TODO: Add tests and install targets if needed.