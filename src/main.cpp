#include <iostream>
#include <Blackjack.hpp>
int main() {
  try {
    Blackjack blackjack;
    blackjack.Run();
    return 0;
  } catch (std::string& e) {
    if (e=="GLFW Failed To Load") {
      std::cout << "GLFW Failed To Load" << std::endl;
      return 1;
    }
  }
}