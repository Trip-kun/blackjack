#pragma once
#define GLEW_STATIC
#include <random>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "STATE/Gamestate.hpp"
#include "FontCache.hpp"
#include "GL/GLProgram.hpp"
#include "VisualCard.hpp"
#include "GL/KeyMonitor.hpp"
#include "GUI/HexicImageButton.hpp"

class Game : public Gamestate {
    enum Phase {
        HIT, STAND, SPLIT, PLAYER_INSURE, INSURE, DEALER, PLAYER, END, SHUFFLE, COLLECTING, DEALING, HIGHBET, LOSE
    };
    enum SplitPhase {
        LEFT, RIGHT, NONE
    };
    enum HighBetSource {
        INSURANCE, DOUBLE, START
    };
public:
    explicit Game(GLFWwindow* window, GLProgram* program, GLProgram* basicProgram, GLProgram *textProgram, Fonts* fonts, Gamestate* menu);
    void Render(Context* ctx) override;
    void Update(double deltaTime) override;
    void HandleInput(KeyFrame*) override;
    void Enter() override;
    void Exit() override;
    void WindowSizeCallback(double width, double height) override;
    void Click(double button, double x, double y) override;
    void Release(double button, double x, double y) override;
    Gamestate* getNextState() override;
    ~Game() override;
private:
    std::default_random_engine generator;
    std::uniform_int_distribution<unsigned long>* visualDistribution;
    Gamestate* nextState = nullptr;
    Gamestate* menu;
    GLFWwindow* window;
    GLProgram* program;
    GLProgram* textProgram;
    Fonts* fonts;
    Phase phase = SHUFFLE;
    std::vector<VisualCard*> playerHand;
    std::vector<VisualCard*> dealerHand;
    std::vector<VisualCard*> splitHand;
    std::vector<VisualCard*> deck;
    std::vector<VisualCard*> discard;
    HexicImageButton<Game*>* hitButton;
    HexicImageButton<Game*>* standButton;
    HexicImageButton<Game*>* splitButton;
    HexicImageButton<Game*>* doubleButton;
    HexicImageButton<Game*>* insureButton;
    HexicImageButton<Game*>* dontInsureButton;
    HexicImageButton<Game*>* dealButton;
    HexicImageButton<Game*>* exitButton;
    HexicImageButton<Game*>* winnerLabel;
    HexicImageButton<Game*>* splitLabel;
    HexicImageButton<Game*>* balanceLabel;
    HexicImageButton<Game*>* betLabel;
    HexicImageButton<Game*>* incrementBet;
    HexicImageButton<Game*>* decrementBet;
    HexicImageButton<Game*>* highBetLabel;
    HexicImageButton<Game*>* restartButton;
    HexicImageButton<Game*>* okayButton;
    bool isWinner=false;
    bool isSplit = false;
    bool isFirstRound=true;
    bool shuffleStarted = false;
    bool shuffleFinished = false;
    double elapsedShuffleTime=0.0;

    bool dealStarted = false;
    double dealTime=0.0;
    bool hasInsured=false;

    bool hasHit=false;
    double hitTime=0.0;

    bool dealerStarted=false;
    double dealerTime=0.0;

    bool isDouble = false;

    bool rightDoubled=false;
    bool leftDoubled=false;

    bool startCollecting=false;
    double collectTime=0.0;
    double max = 5;
    SplitPhase split_phase = NONE;
    double splitTimer=0.0;

    int balance = 1000.0;
    int bet = 20.0;

    HighBetSource highBetSource = START;
};
