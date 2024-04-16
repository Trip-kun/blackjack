#include <iostream>

#include "STATE/Menu.hpp"

Menu::Menu(GLFWwindow* window, GLProgram* program, GLProgram* textProgram, GLProgram* basicProgram, Fonts* fonts) {

    logoTexture = new Texture("img/logo.png");
    this->window=window;
    logo = new Image(logoTexture, program, {-0.5, 0.5, 1.0, 0.5});

    HexicImageButton<Menu*>::setWidth(1280);
    HexicImageButton<Menu*>::setHeight(720);
    startButton = new HexicImageButton<Menu*>(basicProgram, textProgram, fonts, "Start Game!", {-(720.0/1280.0), -0.3, 2*(720.0/1280.0), 0.3}, {1, 1, 1});
    startButton->onClick([](Menu *menu) {
        menu->nextState = menu->game;
    });
    exitButton = new HexicImageButton<Menu*>(basicProgram, textProgram, fonts, "Exit Game!", {-(720.0/1280.0), -0.61, 2*(720.0/1280.0), 0.3}, {1, 1, 1});
    exitButton->onClick([](Menu *menu) {
        glfwSetWindowShouldClose(menu->window, true);
    });
    game = new Game(window, program, basicProgram, textProgram, fonts, this);
}
void Menu::Render(Context *ctx) {
    glClearColor(0.0f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    logo->Draw(ctx);
    startButton->Draw(ctx);
    exitButton->Draw(ctx);
}
void Menu::Update(double deltaTime) {
}
void Menu::HandleInput(KeyFrame* frame) {
    if (KeyMonitor::getState(window, frame, ESCAPE) == PRESS)
        glfwSetWindowShouldClose(window, true);
}
void Menu::Enter() {
    std::cout << "Entering Menu" << std::endl;
}
void Menu::Exit() {
    std::cout << "Exiting Menu" << std::endl;
    this->nextState = nullptr;
}
Gamestate* Menu::getNextState() {
    return nextState;
}
Menu::~Menu() {
    delete logoTexture;
    delete logo;
    delete startButton;
    delete exitButton;
    delete game;
    //delete hexic;
}
void Menu::Click(double button, double x, double y) {
    startButton->Click(button, x, y, this);
    exitButton->Click(button, x, y, this);
}
void Menu::Release(double button, double x, double y) {
    startButton->Release(button, x, y, this);
    exitButton->Release(button, x, y, this);
}
void Menu::WindowSizeCallback(double width, double height) {
    startButton->setWidth(width);
    startButton->setHeight(height);
    exitButton->setWidth(width);
    exitButton->setHeight(height);
}