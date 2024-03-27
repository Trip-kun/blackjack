#pragma once
#include "Drawable.hpp"
#include "Image.hpp"

class Menu : Drawable{
public:
    Menu();
    void Draw(Context* context) override;
    ~Menu() override;
private:
    Image* logo;
    Texture* logoTexture;
};
