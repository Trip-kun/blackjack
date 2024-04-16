#pragma once
#include "FontCache.hpp"
#include "ImageButton.hpp"
#include "GL/Text.hpp"
#include "GL/Drawable.hpp"
#include "GL/Hexic.hpp"
#include "GUI/Element.hpp"
template <typename T>
class HexicImageButton : public Drawable, public Element<T> {
    ImageButton<T>* button;
    Hexic* hexic;
    Text* text;
    static double textureOffset;
    static unsigned int width;
    static unsigned int height;
public:
    HexicImageButton(GLProgram* programBasic, GLProgram* programText, Fonts* fonts, const char* first_text, Position pos, Color color = {1, 1, 1}) {
        button = new ImageButton<T>(nullptr, nullptr, pos, color); // This will NOT be drawing
        unsigned int fontSize = (height*pos.height)*(256-2.75*textureOffset)/(256);
        text = new Text(programText, fonts->getFont(fontSize),  first_text, pos.x+(((textureOffset*1.0f)/256)*pos.width/2),
                                                                                                   pos.y+(((textureOffset*1.0f)/256)*pos.height/1.15),
                                                                              1.0, color);

        hexic = new Hexic(programBasic, pos, color);
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
        hexic->Draw(ctx);
        text->Draw(ctx);
    }
    void setOffset(double x, double y) {
        button->setOffset(x, y);
        hexic->setOffset(x, y);
        text->setOffset(x+(textureOffset/width), y+(textureOffset/height));
    }
    void setTransform(Transform transform) {
        button->setTransform(transform);
        hexic->setTransform(transform);
        text->setScale(transform.sy);
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
    ~HexicImageButton() override {
        delete button;
        delete text;
        delete hexic;
    }
};
template <typename T>
double HexicImageButton<T>::textureOffset=50;
template <typename T>
unsigned int HexicImageButton<T>::width=0;
template <typename T>
unsigned int HexicImageButton<T>::height=0;