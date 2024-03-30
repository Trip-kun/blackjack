#pragma once

#include "GL/Texture.hpp"
namespace Cards {
    Texture* backImage;
    void load() {
        backImage = new Texture("img/back.png");
    }
    void clean() {
        delete backImage;
    }
}