#pragma once
#include "FontCache.hpp"
#include "ImageButton.hpp"
#include "GL/Drawable.hpp"
#include "GL/Text.hpp"
#include "GUI/Element.hpp"
template <typename T>
class TextImageButton : public Drawable, public Element<T> {
    ImageButton<T>* button;
    Text* text;
    static unsigned int textureOffset;
    static unsigned int width;
    static unsigned int height;
public:
    TextImageButton(Texture* texture, GLProgram* programTexture, GLProgram* programText, Fonts* fonts, const char * first_text, Position pos, Color color = {1, 1, 1}) {
        button = new ImageButton<T>(texture, programTexture, pos, color);
        unsigned int fontSize = (height*pos.height)*(256-2.75*textureOffset)/(256);

        text = new Text(programText, fonts->getFont(fontSize),  first_text, pos.x+(((textureOffset*1.0f)/256)*pos.width/2),
                                                                                                   pos.y+(((textureOffset*1.0f)/256)*pos.height/1.15),
                                                                              1.0, color);
    }
    static void setTextureOffset(int offset) {
        textureOffset=offset;
    }
    static void setWidth(unsigned int _width) {
        width=_width;
    }
    static void setHeight(unsigned int _height) {
        height=_height;
    }
    void Draw(Context* ctx) override {
        button->Draw(ctx);
        text->Draw(ctx);
    }
    void setOffset(double x, double y) {
        button->setOffset(x, y);
        text->setOffset(x+(textureOffset/width), y+(textureOffset/height));
    }
    void setTransform(Transform transform) {
        button->setTransform(transform);
        text->setScale(transform.sy);
    }
    void setTexture(Texture* texture) {
        button->setTexture(texture);
    }
    void setText(const char* text) {
        this->text->setText(text);
    }
    void setColor(Color color) {
        button->setColor(color);
        text->setColor(color);
    }
    void setScale(double scale) {
        button->setScale(scale);
        text->setScale(scale);
    }
    void Click(double button_a, double x, double y, T t) override {
        button->Click(button_a, x, y, t);
    }
    void Release(double button_a, double x, double y, T t) override {
        button->Release(button_a, x, y, t);
    }
    unsigned int onClick(void (*func)(T)) {
        return button->onClick(func);
    }
    unsigned int onRelease(void (*func)(T)) {
        return button->onRelease(func);
    }
    void removeOnClick(unsigned int id) {
        button->removeOnClick(id);
    }
    void removeOnRelease(unsigned int id) {
        button->removeOnRelease(id);
    }
    ~TextImageButton() override {
        delete button;
        delete text;
    }

};
template <typename T>
unsigned int TextImageButton<T>::textureOffset=50;
template <typename T>
unsigned int TextImageButton<T>::width=0;
template <typename T>
unsigned int TextImageButton<T>::height=0;