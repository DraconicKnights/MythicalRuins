cmake_minimum_required(VERSION 3.28)
project(MythicalRuins)

set(CMAKE_CXX_STANDARD 20)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Dependencies
set(RAYLIB_VERSION 5.5)
find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
    include(FetchContent)
    FetchContent_Declare(
            raylib
            DOWNLOAD_EXTRACT_TIMESTAMP OFF
            URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
    )
    FetchContent_GetProperties(raylib)
    if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
        set(FETCHCONTENT_QUIET NO)
        FetchContent_MakeAvailable(raylib)
    endif()
endif()

# Our Project

add_executable(MythicalRuins main.cpp
        Core/Application.cpp
        Core/Application.h
        Core/InputEventListener.cpp
        Core/InputEventListener.h
        Core/InputActions.h
        Core/Mouse.h
        Utils/Logger.cpp
        Utils/Logger.h
        Core/System/SystemCore.h
        Core/System/SystemManager.cpp
        Core/System/SystemManager.h
        Core/System/SystemsControllers/PlayerController.cpp
        Core/System/SystemsControllers/PlayerController.h
        Core/System/NetworkCore.h
        Core/System/SystemsControllers/RendererController.cpp
        Core/System/SystemsControllers/RendererController.h
        Core/Render/Object/Object.h
        Core/Render/Entity/Entity.h
        Core/Render/Entity/Entites/Player.cpp
        Core/Render/Entity/Entites/Player.h
        Core/World/ObjectLoaderManager.h
        Core/System/SystemsControllers/MainMenuController.cpp
        Core/System/SystemsControllers/MainMenuController.h
        Core/System/SystemsControllers/PhysicsController.cpp
        Core/System/SystemsControllers/PhysicsController.h
        Core/Render/Object/Objects/BoundingBox.cpp
        Core/Render/Object/Objects/BoundingBox.h
)

target_link_libraries(${PROJECT_NAME} raylib)

if (${PLATFORM} STREQUAL "Web")
    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html") # Tell Emscripten to build an example.html file.
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s USE_GLFW=3 -s ASSERTIONS=1 -s WASM=1 -s ASYNCIFY -s GL_ENABLE_GET_PROC_ADDRESS=1")
endif()

# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()

# === IMGUI ===
set(IMGUI_DIR "E:/CLionProjects/Libary/Frameworks/imgui")

set(IMGUI_SOURCES
        ${IMGUI_DIR}/imgui.cpp
        ${IMGUI_DIR}/imgui_draw.cpp
        ${IMGUI_DIR}/imgui_widgets.cpp
        ${IMGUI_DIR}/imgui_tables.cpp
        ${IMGUI_DIR}/imgui_demo.cpp  # optional
        ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
        ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

target_sources(MythicalRuins PRIVATE ${IMGUI_SOURCES})

target_include_directories(MythicalRuins PRIVATE
        ${IMGUI_DIR}
        ${IMGUI_DIR}/backends
)

# === rlImGui (raylib + Dear ImGui bridge) ===
set(RLIMGUI_DIR "E:/CLionProjects/Libary/Frameworks/RLMGUI")

set(RLIMGUI_SOURCES
        ${RLIMGUI_DIR}/rlImGui.cpp
        # ${RLIMGUI_DIR}/imgui_demo.cpp  # optional
)

target_sources(MythicalRuins PRIVATE ${RLIMGUI_SOURCES})

target_include_directories(MythicalRuins PRIVATE
        ${RLIMGUI_DIR}
)

# If rlImGui needs OpenGL loader headers, raylib already provides them.
# If it needs GLFW headers, point at raylib's vendored GLFW include:
target_include_directories(MythicalRuins PRIVATE
        ${raylib_SOURCE_DIR}/src/external/glfw/include
)

