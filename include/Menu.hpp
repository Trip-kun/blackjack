#pragma once
#include "GL/Drawable.hpp"
#include "GL/Image.hpp"

class Menu : Drawable{
public:
    Menu();
    void Draw(Context* context) override;
    ~Menu() override;
private:
    Image* logo;
    Texture* logoTexture;
};
