

#include "Menu.hpp"

Menu::Menu() {
    logoTexture = new Texture("/home/trip-kun/cpp2/sem/src/img/logo.png");
}
void Menu::Draw(Context *context) {

}
Menu::~Menu() {
    delete logoTexture;
}
