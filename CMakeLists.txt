cmake_minimum_required(VERSION 3.3 FATAL_ERROR)
project(KMblackjack)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

set (CMAKE_CXX_STANDARD 17)
add_executable(${PROJECT_NAME} ./src/main.cpp
        src/Blackjack.cpp
        src/GL/Shader.cpp
        src/GL/GLProgram.cpp
        src/GL/Context.cpp
        include/GL/Context.hpp
        src/GL/Texture.cpp
        include/STATE/Gamestate.hpp
        include/GL/Texture.hpp
        include/GL/Drawable.hpp
        include/GL/shaders.hpp
        src/GL/Image.cpp
        include/GL/Image.hpp
        include/Card.hpp
        include/Deck.hpp
        src/VisualCard.cpp
        include/VisualCard.hpp
        include/tween.hpp
        include/cards.hpp
        src/STATE/Menu.cpp
        include/STATE/Menu.hpp
        src/GL/Font.cpp
        include/GL/Font.hpp
        include/FontCache.hpp
        src/GL/Text.cpp
        include/GL/Text.hpp
        include/GUI/Element.hpp
        include/GUI/ImageButton.hpp
        include/GL/Transforms.hpp
        include/GUI/TextImageButton.hpp
        src/STATE/Game.cpp
        include/STATE/Game.hpp
        include/GL/Hexic.hpp
        src/GL/Hexic.cpp
        include/GUI/HexicImageButton.hpp
        include/GL/KeyMonitor.hpp
        src/GL/KeyMonitor.cpp
)
set (GLEW_VERBOSE 1)
target_include_directories(${PROJECT_NAME} PUBLIC ./include/)
set(OpenGL_GL_PREFERENCE GLVND)
find_package(glfw3 3.3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(Freetype REQUIRED)
find_package(soil REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm)
target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL)
target_link_libraries(${PROJECT_NAME} PUBLIC Freetype::Freetype)

