#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "STATE/Gamestate.hpp"
#include "FontCache.hpp"
#include "GL/GLProgram.hpp"
#include "VisualCard.hpp"
#include "GUI/TextImageButton.hpp"

class Game : public Gamestate {
    enum Phase {
        HIT, STAND, SPLIT, DOUBLE, INSURE, DEALER, PLAYER, END
    };
public:
    explicit Game(GLFWwindow* window, GLProgram* program, GLProgram* textProgram, Fonts* fonts, Gamestate* menu);
    void Render(Context* ctx) override;
    void Update(double deltaTime) override;
    void HandleInput() override;
    void Enter() override;
    void Exit() override;
    void WindowSizeCallback(double width, double height) override;
    void Click(double button, double x, double y) override;
    void Release(double button, double x, double y) override;
    Gamestate* getNextState() override;
    ~Game() override;
private:
    Gamestate* nextState = nullptr;
    Gamestate* menu;
    GLFWwindow* window;
    GLProgram* program;
    GLProgram* textProgram;
    Fonts* fonts;
    std::vector<VisualCard*> playerHand;
    std::vector<VisualCard*> dealerHand;
    std::vector<VisualCard*> deck;
    std::vector<VisualCard*> discard;
    TextImageButton<Game*>* hitButton;
    TextImageButton<Game*>* standButton;
    TextImageButton<Game*>* splitButton;
    TextImageButton<Game*>* doubleButton;
    TextImageButton<Game*>* insureButton;
    TextImageButton<Game*>* dealButton;
    TextImageButton<Game*>* exitButton;
};
