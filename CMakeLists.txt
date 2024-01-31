cmake_minimum_required(VERSION 3.3 FATAL_ERROR)
project(KMblackjack)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)


set (CMAKE_CXX_STANDARD 11)
include_directories(${PROJECT_NAME} PUBLIC ./include)
add_executable(${PROJECT_NAME} ./src/main.cpp)
set(OpenGL_GL_PREFERENCE GLVND)
find_package(glfw3 3.3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL)
target_link_libraries(${PROJECT_NAME} PUBLIC GLEW::glew)
target_link_libraries(${PROJECT_NAME} PUBLIC glfw)
