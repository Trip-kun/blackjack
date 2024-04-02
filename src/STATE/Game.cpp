#include "STATE/Game.hpp"

Game::Game(GLFWwindow *window, GLProgram *program, GLProgram *textProgram, Fonts *fonts, Gamestate* menu) {
    this->window=window;
    this->program=program;
    this->textProgram=textProgram;
    this->fonts=fonts;
    this->menu=menu;
    TextImageButton<Game*>::setWidth(1280);
    TextImageButton<Game*>::setHeight(720);
    this->exitButton = new TextImageButton<Game*>(new Texture("img/button_10_3.png"), program, textProgram, fonts, "Exit Game!", {-1, 0.9, 1.0/3.0, 0.1}, {1, 1, 1});
    exitButton->onClick([](Game *game) {
        game->nextState=game->menu;
    });
}
void Game::Render(Context *ctx) {
    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    int c;
    for (auto &card : playerHand) {
        card->Draw(ctx);
    }
    for (auto &card : dealerHand) {
        card->Draw(ctx);
    }
    c=0;
    for (auto &card : deck) {
        card->Draw(ctx);
        if (c++>5) break;
    }
    c=0;
    for (auto &card : discard) {
        card->Draw(ctx);
        if (c++>5) break;
    }
    exitButton->Draw(ctx);
}
void Game::Update(double deltaTime) {
}
void Game::HandleInput() {
}
void Game::Enter() {
    std::cout << "Entering Game" << std::endl;
}
void Game::Exit() {
    std::cout << "Exiting Game" << std::endl;
    this->nextState = nullptr;
}
void Game::WindowSizeCallback(double width, double height) {
    exitButton->setWidth(width);
    exitButton->setHeight(height);
}
void Game::Click(double button, double x, double y) {
    exitButton->Click(button, x, y, this);
}
void Game::Release(double button, double x, double y) {
    exitButton->Release(button, x, y, this);
}
Gamestate *Game::getNextState() {
    return nextState;
}
Game::~Game() {
    delete exitButton;
}