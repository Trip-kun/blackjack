#pragma once
#include "Texture.hpp"
#include "Context.hpp"
class Drawable {
public:
    virtual ~Drawable() = default;

    virtual void Draw(Context*) = 0;
};