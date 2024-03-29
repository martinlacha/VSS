set(EXECUTABLE_NAME ${PROJECT_NAME})

# cmake -S . -B build

file(GLOB_RECURSE cpp_files "./*.cpp")
file(GLOB_RECURSE h_files "./*.h")
file(GLOB_RECURSE hpp_files "./*.hpp")

add_executable(${EXECUTABLE_NAME}
    ${cpp_files}
    ${h_files}
    ${hpp_files}

    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imgui.h
    ${imgui_SOURCE_DIR}/imgui_demo.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_internal.h
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp

    ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp

    ${implot_SOURCE_DIR}/implot.cpp
    ${implot_SOURCE_DIR}/implot.h
    ${implot_SOURCE_DIR}/implot_demo.cpp
    ${implot_SOURCE_DIR}/implot_internal.h
    ${implot_SOURCE_DIR}/implot_items.cpp
        simulation/vehicles/vehicle.cpp simulation/vehicles/vehicle.h simulation/map/map.h simulation/map/map.cpp simulation/cell.cpp simulation/cell.h simulation/simulation.cpp simulation/simulation.h simulation/map/semaphore.cpp simulation/map/semaphore.h simulation/map/crossroad.cpp simulation/map/crossroad.h simulation/vehicles/path.cpp simulation/vehicles/path.h simulation/configuration.cpp simulation/configuration.h simulation/map/semaphore_waiting_place.cpp simulation/map/semaphore_waiting_place.h)

target_compile_definitions(${EXECUTABLE_NAME}
    PRIVATE
    GLEW_STATIC
)

target_include_directories(${EXECUTABLE_NAME}
    PRIVATE
    ${imgui_SOURCE_DIR}/
)

target_include_directories(${EXECUTABLE_NAME}
    PRIVATE
    ${implot_SOURCE_DIR}/
)

if(WIN32)
    target_link_libraries(${EXECUTABLE_NAME}
        PRIVATE
        glfw
        libglew_static
        $<$<CXX_COMPILER_ID:GNU>:opengl32.a>
        $<$<CXX_COMPILER_ID:MSVC>:opengl32.lib>
    )
else()
    target_link_libraries(${EXECUTABLE_NAME}
        PRIVATE
        glfw
        libglew_static
    )
endif()

add_custom_command(
        TARGET simulation POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/imgui.ini $<TARGET_FILE_DIR:simulation>
)
