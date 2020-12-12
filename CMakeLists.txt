cmake_minimum_required(VERSION 3.10)

project(imgui-example)

add_subdirectory(external/glad)

file(GLOB SRCFILES
    ${CMAKE_SOURCE_DIR}/*.cpp
)
add_executable(${PROJECT_NAME}
    ${SRCFILES}
)

target_include_directories(${PROJECT_NAME} PUBLIC
    /usr/local/include/imgui
    /usr/include/eigen3
    ${CMAKE_SOURCE_DIR}/include
)
target_link_libraries(${PROJECT_NAME}
    igl implot imgui imgui_impl_glfw 
    glfw glad pthread
)