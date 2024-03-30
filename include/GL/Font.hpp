#pragma once
#include <ft2build.h>
#include <glm/vec2.hpp>
#include "GL/glew.h"
#include FT_FREETYPE_H
class Font {
public:
    Font(FT_Face face, int size);
    struct Character {
        unsigned int TextureID;
        glm::ivec2 Size;
        glm::ivec2 Bearing;
        FT_Pos Advance;
    };
    Character* getCharacter(unsigned char c);
private:
    FT_Face face;
    Character characters[128];
};
