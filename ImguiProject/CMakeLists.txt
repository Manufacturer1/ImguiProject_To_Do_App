# CMakeList.txt : CMake project for ImguiProject, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (ImguiProject "ImguiProject.cpp"  "UseImgui.h" "UseImgui.cpp" "ManageItems.h" "ImGuiStyles.h"  "loadTexture.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ImguiProject PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.

set(glad_DIR "C:/Users/Mihai/AppData/Local/cache/Microsoft VS Code/tools/vcpkg/installed/x64-windows/share/glad")
find_package(glad CONFIG REQUIRED)	
target_link_libraries(ImguiProject PRIVATE glad::glad)

set(glfw3_DIR "C:/Users/Mihai/AppData/Local/cache/Microsoft VS Code/tools/vcpkg/installed/x64-windows/share/glfw3")
find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(ImguiProject PRIVATE glfw)

set(imgui_DIR "C:/Users/Mihai/AppData/Local/cache/Microsoft VS Code/tools/vcpkg/installed/x64-windows/share/imgui")
find_package(imgui CONFIG REQUIRED)
target_link_libraries(ImguiProject PRIVATE imgui::imgui)



set(Stb_INCLUDE_DIR "C:/Users/Mihai/AppData/Local/cache/Microsoft VS Code/tools/vcpkg/installed/x64-windows/include")
target_include_directories(ImguiProject PRIVATE ${Stb_INCLUDE_DIR})


set(gl3w_DIR "C:/Users/Mihai/AppData/Local/cache/Microsoft VS Code/tools/vcpkg/installed/x64-windows/share/gl3w" )
find_package(gl3w CONFIG REQUIRED)
target_link_libraries(ImguiProject PRIVATE unofficial::gl3w::gl3w)


add_custom_command(TARGET ImguiProject POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "C:/Users/Mihai/AppData/Local/cache/Microsoft VS Code/tools/vcpkg/installed/x64-windows/bin/gl3w.dll"
        $<TARGET_FILE_DIR:ImguiProject>)

add_custom_command(TARGET ImguiProject POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "C:/Users/Mihai/AppData/Local/cache/Microsoft VS Code/tools/vcpkg/installed/x64-windows/bin/glfw3.dll"
        $<TARGET_FILE_DIR:ImguiProject>)




