cmake_minimum_required(VERSION 3.24.1)

set(CMAKE_CXX_STANDARD 20) 

set(PROJECT_NAME "Harmonizer")
set(PRODUCT_NAME "Harmonizer")
set(COMPANY_NAME "funnyscar")

project(${PROJECT_NAME} VERSION ${CURRENT_VERSION})

add_executable(main src/main.cpp)

include(cmake/CPM.cmake)

# RTAudio
CPMAddPackage(
	NAME rtaudio
	GITHUB_REPOSITORY thestk/rtaudio
	GIT_TAG 6.0.1
)

# ImGui
CPMAddPackage(
	NAME imgui
	GITHUB_REPOSITORY ocornut/imgui
	GIT_TAG v1.91.5
)
# No cmake support
add_library(imgui STATIC
    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
)
target_include_directories(imgui PUBLIC ${imgui_SOURCE_DIR}/backends)

# GLFW
CPMAddPackage(
    NAME glfw
    GITHUB_REPOSITORY glfw/glfw
    GIT_TAG 3.4
)

# OpenGL
find_package(OpenGL REQUIRED)
get_target_property(OPENGL_TARGET OpenGL::GL NAME)
message(STATUS "OpenGL target: ${OPENGL_TARGET}")

# FFTW3
CPMAddPackage(
	NAME fftw3
	VERSION 3.3.10
	URL https://www.fftw.org/fftw-3.3.10.tar.gz
)


set_target_properties(main PROPERTIES CXX_STANDARD 17)
target_link_libraries(main PRIVATE rtaudio fftw3 imgui glfw ${OPENGL_TARGET})
