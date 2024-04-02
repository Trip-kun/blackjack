//
// Created by trip-kun on 2/6/24.
//

#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <chrono>
#include "STATE/Gamestate.hpp"
#include "STATE/Menu.hpp"
#include "GL/Context.hpp"
#include "GUI/TextImageButton.hpp"
class Blackjack {
public:
    Blackjack();
    ~Blackjack();
    void Run();
    void static windowSizeCallback(GLFWwindow* window, int width, int height);
    double static getWidth();
    double static getHeight();
    std::pair<double, double> static getOpenGLMouseCoords(GLFWwindow* window);
private:
    GLFWwindow* window;
    Context* context;
    Gamestate* currentState;
    Menu* menu;
    Fonts* fonts;
    void processInput();
    static int width, height;
    std::chrono::time_point<std::chrono::high_resolution_clock> lastTime = std::chrono::high_resolution_clock::now();
    int leftButton, rightButton, middleButton = GLFW_RELEASE;
};
