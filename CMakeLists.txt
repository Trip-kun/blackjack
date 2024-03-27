cmake_minimum_required(VERSION 3.3 FATAL_ERROR)
project(KMblackjack)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)


set (CMAKE_CXX_STANDARD 11)
add_executable(${PROJECT_NAME} ./src/main.cpp
        src/Blackjack.cpp
        src/Shader.cpp
        src/GLProgram.cpp
        src/Context.cpp
        include/Context.hpp
        src/Texture.cpp
        include/Texture.hpp
        include/Drawable.hpp
        include/shaders.hpp
        src/Image.cpp
        include/Image.hpp
        include/Card.hpp
        include/Deck.hpp
        src/VisualCard.cpp
        include/VisualCard.hpp
        include/tween.hpp
        include/cards.hpp
        src/Menu.cpp
        include/Menu.hpp
        src/Font.cpp
        include/Font.hpp
        include/FontCache.hpp
        src/Text.cpp
        include/Text.hpp)
target_include_directories(${PROJECT_NAME} PUBLIC ./include/)
set(OpenGL_GL_PREFERENCE GLVND)
find_package(glfw3 3.3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(Freetype REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm)
target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL)
target_link_libraries(${PROJECT_NAME} PUBLIC GLEW::glew)
target_link_libraries(${PROJECT_NAME} PUBLIC glfw)
target_link_libraries(${PROJECT_NAME} PUBLIC /usr/local/lib/libSOIL.a)
target_link_libraries(${PROJECT_NAME} PUBLIC Freetype::Freetype)