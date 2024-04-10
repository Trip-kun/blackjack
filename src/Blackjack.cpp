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
void errorCallback(int error, const char* description) {
    std::cerr << "Error: " << description << std::endl;
}
Blackjack::Blackjack() {
    std::cout << "It's time to gamble!" << std::endl;
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);
    this->window = glfwCreateWindow(1280, 720, "Hello, World", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        throw std::string("GLFW Failed To Load");
    }
    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();

    glfwSetWindowSizeCallback(window, windowSizeCallback);
    glfwSetErrorCallback(errorCallback);
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
    glEnable(GL_MULTISAMPLE);
    Cards::getCards();
    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    fonts = new Fonts();

    fonts->init();
    menu = new Menu(window, Shaders::texture, Shaders::text, Shaders::basic, fonts);
    menu->Enter();
    currentState = menu;

}
void Blackjack::Run() {
    unsigned int* indices = new unsigned int[]{
        0, 1, 3,
        1, 2, 3
        };
    double* vertices = new double[]{
         0.2,  0.2, 1.0, 1.0, 1.0,
         0.2, -0.2, 1.0, 1.0, 1.0,
        -0.2, -0.2, 1.0, 1.0, 1.0,
        -0.2,  0.2, 1.0, 1.0, 1.0,
    };
    unsigned int VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, 20*sizeof(double), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6*sizeof(unsigned int), indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_DOUBLE, GL_FALSE, 5 * sizeof(double), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_DOUBLE, GL_FALSE, 5 * sizeof(double), (void*)(2*sizeof(double)));
    glEnableVertexAttribArray(1);
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
        Shaders::basic->use(context);
        glCullFace(GL_FRONT);
        glBindVertexArray(VAO);
        glm::mat4 proj = glm::mat4(1.0);
        //glUniformMatrix4fv(Shaders::basic->getUniformLocation("proj"), 1, GL_FALSE, glm::value_ptr(proj));
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        currentState->WindowSizeCallback(width, height);
        glfwSwapBuffers(window);
        /*
        const char ** desc;
        int j = glfwGetError(desc);
        std::cout << "Error: " << j << std::endl;
        for (int i = 0; i < 10; i++) {
            if (j!= 0 && desc[i] == nullptr)
                break;
            if (j!=0)
                std::cout << "Error: " << desc[i] << std::endl;
        }
        //*/
        //*/


        glfwPollEvents();
    }
    currentState->Exit();
    std::cout << "Gambling Time is Over!" << std::endl;
}
Blackjack::~Blackjack() {
    delete Cards::getCards();
    Shaders::clean(context);
    fonts->clean();
    delete context;
    delete menu;
    delete fonts;
    delete oldFrame;
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

    KeyFrame* frame = new KeyFrame; // Frame pointers need to aleternate between frames to prevent reuse of the same address in the next frame
    currentState->HandleInput(frame);
    if (!frameStarted) {
        frameStarted=true;
    } else {
        delete oldFrame;
    }
    oldFrame=frame;
}