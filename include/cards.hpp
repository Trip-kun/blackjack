#pragma once

#include "Texture.hpp"
namespace Cards {
    Texture* backImage;
    void load() {
        backImage = new Texture("/home/trip-kun/cpp2/sem/src/img/back.png");
    }
    void clean() {
        delete backImage;
    }
}