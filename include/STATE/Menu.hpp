#pragma once
#include "Game.hpp"
#include "GL/Hexic.hpp"
#include "STATE/Gamestate.hpp"
#include "GUI/HexicImageButton.hpp"
#include "GL/Image.hpp"
#include "GL/Text.hpp"

class Menu : public Gamestate{
public:
    explicit Menu(GLFWwindow* window, GLProgram* program, GLProgram* textProgram, GLProgram* basicProgram, Fonts* fonts);
    void Render(Context* ctx) override;
    void Update(double deltaTime) override;
    void HandleInput(KeyFrame*) override;
    void Enter() override;
    void Exit() override;
    void WindowSizeCallback(double width, double height) override;
    void Click(double button, double x, double y) override;
    void Release(double button, double x, double y) override;
    Gamestate* getNextState() override;
    ~Menu() override;
private:
    Image* logo;
    Texture* logoTexture;
    HexicImageButton<Menu*>* startButton;
    GLFWwindow* window;
    HexicImageButton<Menu*>* exitButton;
    Gamestate* nextState = nullptr;
    Game* game;
};
