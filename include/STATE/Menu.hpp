#pragma once
#include "STATE/Gamestate.hpp"
#include "GUI/ImageButton.hpp"
#include "GL/Image.hpp"
#include "GL/Text.hpp"

class Menu : public Gamestate{
public:
    explicit Menu(GLProgram* program, GLProgram* textProgram, Font* font);
    void Render(Context* ctx) override;
    void Update(double deltaTime) override;
    void HandleInput() override;
    void Enter() override;
    void Exit() override;
    void Click(double button, double x, double y) override;
    void Release(double button, double x, double y) override;
    Gamestate* getNextState() override;
    ~Menu() override;
private:
    Image* logo;
    Texture* logoTexture;
    ImageButton<Menu*>* startButton;
    Text* text;
    void incrementCount();
    double count = 0;
};
