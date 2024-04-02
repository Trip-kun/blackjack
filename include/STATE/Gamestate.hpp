#pragma once
#include "GL/Context.hpp"

class Gamestate {
public:
    virtual ~Gamestate() =default;
    virtual void Render(Context* ctx) = 0;
    virtual void Update(double deltaTime) = 0;
    virtual void HandleInput() = 0;
    virtual void WindowSizeCallback(double width, double height) = 0;
    virtual void Enter() = 0;
    virtual void Click(double button, double x, double y) = 0;
    virtual void Release(double button, double x, double y) = 0;
    virtual void Exit() = 0;
    virtual Gamestate* getNextState() = 0;
};
