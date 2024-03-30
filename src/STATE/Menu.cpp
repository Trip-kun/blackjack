#include <iostream>

#include "STATE/Menu.hpp"

Menu::Menu(GLProgram* program, GLProgram* textProgram, Font* font) {
    logoTexture = new Texture("img/logo.png");
    logo = new Image(logoTexture, program, -0.5, 0.5, 1.0, 0.5);
    startButton = new ImageButton<Menu*>(new Texture("img/logo.png"), program, -0.3, -0.1, 0.6, 0.1, 1, 1, 1);
    startButton->onClick([](Menu *menu) {
        menu->incrementCount();

    });
    text = new Text(textProgram, font, "Count: 0", 0, 0, 1.0, 1.0, 1.0, 1.0);
}
void Menu::Render(Context *ctx) {
    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    logo->Draw(ctx);
    startButton->Draw(ctx);
    text->Draw(ctx);
}
void Menu::Update(double deltaTime) {
}
void Menu::HandleInput() {
}
void Menu::Enter() {
    std::cout << "Entering Menu" << std::endl;
}
void Menu::Exit() {
    std::cout << "Exiting Menu" << std::endl;
}
Gamestate* Menu::getNextState() {
    return nullptr;
}
Menu::~Menu() {
    delete logoTexture;
    delete logo;
    delete startButton;
}
void Menu::Click(double button, double x, double y) {
    startButton->Click(button, x, y, this);
}
void Menu::Release(double button, double x, double y) {
    startButton->Release(button, x, y, this);
}
void Menu::incrementCount() {
    char* countText = new char[64];
    sprintf(countText, "Count: %f", ++count);
    text->setText(countText);
}