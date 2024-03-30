#pragma once
#include <glm/gtc/type_ptr.hpp>
#include "Shader.hpp"
#include "GLProgram.hpp"

namespace Shaders {
    const char * basicVertex = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";
    const char * basicFragment=
        "#version 330 core\n"
        "out vec4 FragColor;"
        "void main()\n"
        "{\n"
        "FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n"
        "}\n"
        "\0";
    /*
    const char * textureVertex=
        "#version 330 core\n"
        "layout (location = 0) in vec2 aPos;\n"
        "layout (location = 1) in vec3 aColor;\n"
        "layout (location = 2) in vec2 aTexCoord;\n"
        "out vec3 ourColor;\n"
        "out vec2 TexCoord;\n"
        "void main()\n"
        "{\n"
        "gl_Position=vec4(aPos, 0.0, 1.0);\n"
        "ourColor=aColor;\n"
        "TexCoord=vec2(aTexCoord.x,1-aTexCoord.y);\n"
        "}\n"
        "\0";
    const char * textureFragment=
        "#version 330 core\n"
        "out vec4 FragColor;\n"
        "in vec3 ourColor;\n"
        "in vec2 TexCoord;\n"
        "uniform sampler2D ourTexture;\n"
        "void main()\n"
        "{\n"
        "FragColor = texture(ourTexture, TexCoord);\n"
        "}\n"
        "\0";
        */
    const char *textureVertex = {
        #include "texture.vs"
    };
    const char *textureFragment = {
        #include "texture.fs"
    };
    const char *textVertex = {
        #include "text.vs"
    };
    const char *textFragment = {
        #include "text.fs"
    };
    Shader* basicV;
    Shader* basicF;
    Shader* textureV;
    Shader* textureF;
    Shader* textV;
    Shader* textF;
    GLProgram* basic;
    GLProgram* texture;
    GLProgram* text;
    glm::mat4 projection = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f);;
    void inline load(Context* ctx) {
        basicV = new Shader(basicVertex, GL_VERTEX_SHADER);
        basicF = new Shader(basicFragment, GL_FRAGMENT_SHADER);
        textureV= new Shader(textureVertex, GL_VERTEX_SHADER);
        textureF = new Shader(textureFragment, GL_FRAGMENT_SHADER);
        textV = new Shader(textVertex, GL_VERTEX_SHADER);
        textF = new Shader(textFragment, GL_FRAGMENT_SHADER);
        basic = new GLProgram(basicV, basicF);
        texture = new GLProgram(textureV, textureF);
        text = new GLProgram(textV, textF);
        text->use(ctx);
        glEnable(GL_CULL_FACE);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glUniformMatrix4fv(text->getUniformLocation("projection"), 1, GL_FALSE, glm::value_ptr(projection));
    }
    void inline clean(Context* ctx) {
        delete basicV;
        delete basicF;
        delete textureV;
        delete textureF;
        delete textV;
        delete textF;
        delete basic;
        delete texture;
        delete text;
    }
}
