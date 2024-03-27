#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <Blackjack.hpp>
#include <chrono>
#include <Shader.hpp>
#include <GLProgram.hpp>
#include <SOIL/SOIL.h>
#include <shaders.hpp>

#include "cards.hpp"
#include "Deck.hpp"
#include "FontCache.hpp"
#include "Image.hpp"
#include "Text.hpp"
#include "Texture.hpp"
#include "VisualCard.hpp"

void processInput(GLFWwindow *window);
void windowSizeCallback(GLFWwindow* window, int width, int height);
std::pair<double, double> getOpenGLMouseCoords(GLFWwindow *window);
int main() {
  Blackjack blackjack;
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* window = glfwCreateWindow(1280, 720, "Hello, World", NULL, NULL);
  if (window == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  GLenum err = glewInit();
  glfwSetWindowSizeCallback(window, windowSizeCallback);
  //Shaders
  Context* ctx = new Context();
  Shaders::load(ctx);
  GLProgram* program = Shaders::texture;
  std::cout << Shaders::textureF->getInfo() << std::endl;
  std::cout << Shaders::textureV->getInfo() << std::endl;
  std::cout << Shaders::basicF->getInfo() << std::endl;
  std::cout << Shaders::basicV->getInfo() << std::endl;
  std::cout << Shaders::textF->getInfo() << std::endl;
  std::cout << Shaders::textV->getInfo() << std::endl;
  Texture texture("/home/trip-kun/Downloads/bee.png");
  Image image(&texture, program, -0.5, -0.5, 1, 1);
  Image image2(&texture, program, -1, -1, 0.5, 0.5);
  Image image3(&texture, program, -1, 0.5, 0.5, 0.5);
  program->use(ctx);
  glEnable(GL_BLEND);
  auto t1 = std::chrono::high_resolution_clock::now();
  Deck deck1, deck2, deck3, deck4, deck5, deck6;
  deck2.put(deck1.pull());
  Deck deck(deck1, deck2);
  Deck deckb(deck3, deck4);
  Deck deckc(deck5, deck6);
  Deck deckd(deck, deckb);
  Deck fdeck(deckd, deckc);
  Cards::load();
  VisualCard::setBackImage(Cards::backImage);
  Texture frontFace("/home/trip-kun/cpp2/sem/src/img/ace_clubs.png");
  VisualCard vcard(Card::Face::ACE, Card::Suit::SPADES, &frontFace, program, 0, 0, 1.2);
  Fonts::init();
  Text text(Shaders::text, Fonts::roboto, "Hello, World", 25.0, 25.0, 1.0, 1.0, 1.0, 1.0);
  vcard.Move(-0.5, -0.5);
  vcard.Flip();
  bool finished=false;
  auto t2 = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> dur = t2-t1;
  std::cout << "Time: " << dur.count();
  //deck.printAll();
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  while (!glfwWindowShouldClose(window)) {
    processInput(window);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    image.Draw(ctx);
    image2.Draw(ctx);
    image3.Draw(ctx);
    vcard.Draw(ctx);
    text.Draw(ctx);
    if (!finished && vcard.getMoveAnimation()==VisualCard::STILL) {
      finished=true;
      vcard.Move(0.0, 0.0);
      vcard.Flip();
    }
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  delete ctx;
}

void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
}
std::pair<double, double> getOpenGLMouseCoords(GLFWwindow *window) {
  double xScreen, yScreen;
  int width, height;
  glfwGetCursorPos(window, &xScreen, &yScreen);
  glfwGetWindowSize(window, &width, &height);
  double x = (2 * (xScreen / width)) - 1;
  double y = (-2 * (yScreen / height)) + 1;
  return {x, y};
}

void windowSizeCallback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}
