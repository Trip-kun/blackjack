#include <iostream>

#include "GL//Font.hpp"

Font::Font(FT_Face face, int size) {
    this->face=face;
    FT_Set_Pixel_Sizes(face, 0, size);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    for (unsigned char c = 0; c<128; c++) {
        if(FT_Load_Char(face, c, FT_LOAD_RENDER)) {
            std::cout << "Could not load character" << std::endl;
            throw "FREETYPE CHARACTER LOAD ERROR";
        }
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        Character character = {
            texture,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            face->glyph->advance.x
        };
        characters[c] = character;
    }

}

Font::Character* Font::getCharacter(unsigned char c) {
    return &characters[c];
}