cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(
    simulation
    VERSION 0.0.1
    DESCRIPTION ""
    HOMEPAGE_URL "%%myurl%%"
    LANGUAGES CXX C
)

include(FetchContent)

FetchContent_Declare(
    glew
    GIT_REPOSITORY https://github.com/Perlmint/glew-cmake.git
    GIT_TAG glew-cmake-2.2.0
)

FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw
    GIT_TAG 3.3.2
)

FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui
    GIT_TAG docking
) 

FetchContent_Declare(
    implot
    GIT_REPOSITORY https://github.com/epezent/implot
    #GIT_TAG v0.14
    GIT_TAG 33c5a965f55f80057f197257d1d1cdb06523e963
)

FetchContent_MakeAvailable(glew glfw imgui implot)

set_property(DIRECTORY ${glew_SOURCE_DIR} PROPERTY EXCLUDE_FROM_ALL YES)
set_property(DIRECTORY ${glfw_SOURCE_DIR} PROPERTY EXCLUDE_FROM_ALL YES)

add_subdirectory(src)
