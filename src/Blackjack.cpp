//
// Created by trip-kun on 2/6/24.
//
#define GLEW_STATIC
#include "Blackjack.hpp"
#include "cards.hpp"
#include "FontCache.hpp"
#include "GL/shaders.hpp"
int Blackjack::height=720;
int Blackjack::width=1280;
Blackjack::Blackjack() {
    std::cout << "It's time to gamble!" << std::endl;
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    this->window = glfwCreateWindow(1280, 720, "Hello, World", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        throw std::string("GLFW Failed To Load");
    }
    glfwMakeContextCurrent(window);
    GLenum err = glewInit();
    glfwSetWindowSizeCallback(window, windowSizeCallback);
    this->context = new Context();
    Shaders::load(context);
    GLProgram* program = Shaders::texture;
    std::cout <<"Texture Fragment Shader: " << Shaders::textureF->getInfo() << std::endl;
    std::cout <<"Texture Vertex Shader: " << Shaders::textureV->getInfo() << std::endl;
    std::cout <<"Basic Fragment Shader: " << Shaders::basicF->getInfo() << std::endl;
    std::cout <<"Basic Vertex Shader: " << Shaders::basicV->getInfo() << std::endl;
    std::cout <<"Text Fragment Shader: " << Shaders::textF->getInfo() << std::endl;
    std::cout <<"Text Vertex Shader: " << Shaders::textV->getInfo() << std::endl;
    program->use(context);
    glEnable(GL_BLEND);
    Cards::load();
    Fonts::init();
    menu = new Menu(Shaders::texture, Shaders::text, Fonts::roboto);
    menu->Enter();
    currentState = menu;
}
void Blackjack::Run() {
    while (!glfwWindowShouldClose(window)) {
        processInput();
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        currentState->Render(context);
        std::chrono::time_point<std::chrono::high_resolution_clock> newTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> deltaTime = std::chrono::duration_cast<std::chrono::duration<double>>(newTime - lastTime);
        currentState->Update(deltaTime.count());
        lastTime = newTime;
        Gamestate* nextState = currentState->getNextState();
        if (nextState != nullptr) {
            currentState->Exit();
            currentState = nextState;
            currentState->Enter();
        }
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    currentState->Exit();
    std::cout << "Gambling Time is Over!" << std::endl;
}
Blackjack::~Blackjack() {
    Cards::clean();
    Shaders::clean(context);
    Fonts::clean();
    delete context;
    delete menu;
    glfwTerminate();
}
void Blackjack::windowSizeCallback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
    Blackjack::width=width;
    Blackjack::height=height;
    Text::setWidth(width);
    Text::setHeight(height);
}
double Blackjack::getHeight() {
    return height;
}
double Blackjack::getWidth() {
    return width;
}
std::pair<double, double> Blackjack::getOpenGLMouseCoords(GLFWwindow *window) {
    double xScreen, yScreen;
    int width, height;
    glfwGetCursorPos(window, &xScreen, &yScreen);
    glfwGetWindowSize(window, &width, &height);
    double x = (2 * (xScreen / width)) - 1;
    double y = (-2 * (yScreen / height)) + 1;
    return {x, y};
}
void Blackjack::processInput() {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    int left = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
    int right = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT);
    int middle = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE);
    if (leftButton!=left) {
        if (leftButton==GLFW_PRESS)
            currentState->Release(GLFW_MOUSE_BUTTON_LEFT, getOpenGLMouseCoords(window).first, getOpenGLMouseCoords(window).second);
        else
            currentState->Click(GLFW_MOUSE_BUTTON_LEFT, getOpenGLMouseCoords(window).first, getOpenGLMouseCoords(window).second);
        leftButton = left;
    }
    if (rightButton!=right) {
        if (rightButton==GLFW_PRESS)
            currentState->Release(GLFW_MOUSE_BUTTON_RIGHT, getOpenGLMouseCoords(window).first, getOpenGLMouseCoords(window).second);
        else
            currentState->Click(GLFW_MOUSE_BUTTON_RIGHT, getOpenGLMouseCoords(window).first, getOpenGLMouseCoords(window).second);
        rightButton = right;
    }
    if (middleButton!=middle) {
        if (middleButton==GLFW_PRESS)
            currentState->Release(GLFW_MOUSE_BUTTON_MIDDLE, getOpenGLMouseCoords(window).first, getOpenGLMouseCoords(window).second);
        else
            currentState->Click(GLFW_MOUSE_BUTTON_MIDDLE, getOpenGLMouseCoords(window).first, getOpenGLMouseCoords(window).second);
        middleButton = middle;
    }
    currentState->HandleInput();
}