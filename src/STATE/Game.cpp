#include "STATE/Game.hpp"

#include "cards.hpp"
#include "Deck.hpp"
#include "GL/KeyMonitor.hpp"
double getX(int count) {
    double static const out = 0.3/ (1280.0/720.0);
    if (count==0) {
        return out;
    }
    if (count%2 == 1) {
        return (out/2.0)+ ((count-1)/2)*(out/2.0);
    }
    return (out/2.0)+ ((count)/2)*(-out/2.0);
}
double countValue(std::vector<VisualCard*>* hand) {
    int value=0;
    int numAces=0;
    for (int i = 0; i<hand->size(); i++) {
        VisualCard* card = (*hand)[i];
        if (card->getFace() == Card::Face::ACE) {
            numAces++;
        } else {
            switch(card->getFace()) {
                case Card::Face::DUECE: {value+=2; break; }
                case Card::Face::THREE: {value+=3; break;}
                case Card::Face::FOUR: {value+=4; break;}
                case Card::Face::FIVE: {value+=5; break;}
                case Card::Face::SIX: {value+=6; break;}
                case Card::Face::SEVEN: {value+=7; break;}
                case Card::Face::EIGHT: {value+=8; break;}
                case Card::Face::NINE: {value+=9; break;}
                case Card::Face::TEN:
                case Card::Face::JACK:
                case Card::Face::QUEEN:
                case Card::Face::KING: {value+=10; break;}
                default: break;
            }
        }
    }
    while (numAces>0) {
        if (value+11+(numAces-1)<=21) {
            value+=11;
        } else {
            value+=1;
        }
        numAces--;
    }
    return value;
}
Game::Game(GLFWwindow *window, GLProgram *program, GLProgram *basicProgram, GLProgram *textProgram, Fonts *fonts, Gamestate* menu) {
    generator.seed(std::time(nullptr));
    this->visualDistribution = new std::uniform_int_distribution<unsigned long>(0, 1023);
    this->window=window;
    this->program=program;
    this->textProgram=textProgram;
    this->fonts=fonts;
    this->menu=menu;
    HexicImageButton<Game*>::setWidth(1280);
    HexicImageButton<Game*>::setHeight(720);
    Deck deck1(true), deck2(true), deck3(true), deck4(true), deck5(true), deck6(true);
    Deck deckA(deck1, deck2), deckB(deck3, deck4), deckC(deck5, deck6);
    Deck deckD(deckA, deckB), deckE(deckC, deckD);
    VisualCard::setBackImage(Cards::getCards()->getBackImage());
    for (int i=0; i<52*6; i++) {
        Card* card = deckE.pull();
        VisualCard* vcard = new VisualCard(card->getFace(), card->getSuit(), Cards::getCards()->getFrontFace(card->getFace(), card->getSuit()), program, -0.15/ (1280.0/720.0), 0.21, 0.5);
        deck.push_back(vcard);
    }
    this->exitButton = new HexicImageButton<Game*>(basicProgram, textProgram, fonts, "Exit Game!", {-1, 0.9, 1.0/3.0, 0.1}, {1, 1, 1});
    exitButton->onClick([](Game *game) {
        game->nextState=game->menu;
    });
    this-> hitButton = new HexicImageButton<Game*>(basicProgram, textProgram, fonts, "Hit", {-1, -1, 1.0/3.0, 0.1}, {1, 1, 1});
    this->hitButton->onClick([](Game *game) {
        if (game->phase==PLAYER && !game->hasHit) {
            game->playerHand.emplace_back(*(game->deck.begin()));
            game->playerHand.back()->Move(getX(game->playerHand.size()), -0.9);
            game->playerHand.back()->Flip();
            game->deck.erase(game->deck.begin());
            game->hasHit=true;
            game->phase=HIT;
        }
    });
    this-> standButton = new HexicImageButton<Game*>(basicProgram, textProgram, fonts, "Stand", {-(2.0/3.0), -1, 1.0/3.0, 0.1}, {1, 1, 1});
    this->standButton->onClick([](Game *game) {
        if (game->phase==PLAYER) {
            game->phase=DEALER;
        }
    });
    this-> splitButton = new HexicImageButton<Game*>(basicProgram, textProgram, fonts, "Split", {-(1.0/3.0), -1, 1.0/3.0, 0.1}, {1, 1, 1});
    this->splitButton->onClick([](Game *game) {
        if (game->phase==PLAYER) {

        }
    });
    this-> doubleButton = new HexicImageButton<Game*>(basicProgram, textProgram, fonts, "Double", {0, -1, 1.0/3.0, 0.1}, {1, 1, 1});
    this->doubleButton->onClick([](Game *game) {
        if (game->phase==PLAYER) {
            game->playerHand.emplace_back(*(game->deck.begin()));
            game->playerHand.back()->Move(getX(game->playerHand.size()), -0.9);
            game->playerHand.back()->Flip();
            game->deck.erase(game->deck.begin());
            game->hasHit=true;
            game->isDouble=true;
            game->phase=HIT;
        }
    });
    this-> insureButton = new HexicImageButton<Game*>(basicProgram, textProgram, fonts, "Insure", {(1.0/3.0), -1, 1.0/3.0, 0.1}, {1, 1, 1});
    this->insureButton->onClick([](Game *game) {
        if (game->phase==PLAYER_INSURE) {
            game->hasInsured=true;
            game->phase=PLAYER;
            if (countValue(&game->dealerHand)==21) {
                game->phase=DEALER;
            }
        }
    });
    this->dontInsureButton = new HexicImageButton<Game*>(basicProgram, textProgram, fonts, "Don't Insure", {(1.0/3.0), -0.9, 1.0/3.0, 0.1}, {1, 1, 1});
    this->dontInsureButton->onClick([](Game *game) {
        if (game->phase==PLAYER_INSURE) {
            game->phase=PLAYER;
        }
    });
    this-> dealButton = new HexicImageButton<Game*>(basicProgram, textProgram, fonts, "Deal", {(2.0/3.0), -1, 1.0/3.0, 0.1}, {1, 1, 1});
    this->dealButton->onClick([](Game *game) {
        if (game->phase==END) {
            game->hasInsured=false;
            game->isFirstRound=false;
            game->phase=DEALING;
        }
    });
    winnerLabel = new HexicImageButton<Game*>(textProgram, textProgram, fonts, "", {0, 0, 1.0/3.0, 0.1}, {1, 1, 1});
}
void Game::Render(Context *ctx) {
    glClearColor((53.0f/255.0f), (101.0f/255.0f), (77.0f/255.0f), 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    int c;
    for (auto &card : playerHand) {
        card->Draw(ctx);
    }
    for (auto &card : dealerHand) {
        card->Draw(ctx);
    }
    c=0;
    for (auto &card : deck) {
        card->Draw(ctx);
        if (c++>this->max) break;
    }
    c=0;
    for (auto &card : discard) {
        card->Draw(ctx);
        if (c++>this->max) break;
    }
    exitButton->Draw(ctx);
    if (phase==PLAYER) {
        hitButton->Draw(ctx);
        standButton->Draw(ctx);
        if (playerHand.size()==2) {
            doubleButton->Draw(ctx);
            if (playerHand[0]->getFace()==playerHand[1]->getFace())
                splitButton->Draw(ctx);
        }
    }
    if (phase==PLAYER_INSURE) {
        insureButton->Draw(ctx);
        dontInsureButton->Draw(ctx);
    }
    if (phase==END) {
        dealButton->Draw(ctx);
        if (isWinner) {
            winnerLabel->Draw(ctx);
        }
    }
}
void Game::Update(double deltaTime) {
    static double shuffleTime=1.0;
    if (phase==SHUFFLE) {
        if (!shuffleStarted && !shuffleFinished) {
            shuffleStarted=true;
            Deck shuffler(false);
            for (auto &card : deck) {
                shuffler.put(card);
            }
            deck.clear();
            for (auto &card : discard) {
                shuffler.put(card);
            }
            discard.clear();
            shuffler.shuffle();
            for (int i=0; i<52*6; i++) {
                Card* card = shuffler.pull();
                VisualCard* vcard = dynamic_cast<VisualCard*>(card);
                double xMove, yMove;
                xMove = (((double) (*visualDistribution)(generator) )/(512.0*1.1)) -(1.0/1.1) + 0.075/ (1280.0/720.0);
                yMove = -((double) (*visualDistribution)(generator))/1024.0;
                vcard->Move(xMove, (yMove*1.4)+0.3);
                deck.push_back(vcard);
                this->max=1000;
            }
        } else if (shuffleFinished==true) {
            if (shuffleStarted) {
                elapsedShuffleTime+=deltaTime;
                if (elapsedShuffleTime>shuffleTime) {
                    shuffleStarted=false;
                    shuffleFinished=false;
                    this->max=5;
                    phase=END;
                }
            } else {
                for (int i=0; i<52*6; i++) {
                    VisualCard* card = deck[i];
                    card->Move(0, 0);
                }
                shuffleStarted=true;
            }
        } else {
            elapsedShuffleTime+=deltaTime;
            if (elapsedShuffleTime>shuffleTime) {
                elapsedShuffleTime=0.0;
                shuffleStarted=false;
                shuffleFinished=true;
            }
        }
    }
    if (phase==DEALING) {
        if (!dealStarted) {
            playerHand.emplace_back(*deck.begin());
            playerHand[0]->Move(getX(playerHand.size()), -0.9);
            playerHand[0]->Flip();
            deck.erase(deck.begin());
            playerHand.emplace_back(*(deck.begin()));
            playerHand[1]->Move(getX(playerHand.size()), -0.9);
            playerHand[1]->Flip();
            deck.erase(deck.begin());
            dealerHand.emplace_back(*(deck.begin()));
            dealerHand[0]->Move(getX(dealerHand.size()), -0.3);
            dealerHand[0]->Flip();
            deck.erase(deck.begin());
            dealerHand.emplace_back(*(deck.begin()));
            dealerHand[1]->Move(getX(dealerHand.size()), -0.3);
            deck.erase(deck.begin());
            dealStarted=true;
        } else {
            dealTime+=deltaTime;
            if (dealTime>shuffleTime) {
                dealTime=0.0;
                dealStarted=false;
                if (dealerHand[0]->getFace() == Card::Face::ACE) {
                    phase=PLAYER_INSURE;
                } else {
                    phase=PLAYER;
                }
                if (dealerHand[0]->getFace() == Card::Face::TEN || dealerHand[0]->getFace() == Card::Face::JACK || dealerHand[0]->getFace() == Card::Face::QUEEN || dealerHand[0]->getFace() == Card::Face::KING) {
                    if (dealerHand[1]->getFace() == Card::Face::ACE) {
                        phase=DEALER; // Waste of time to do more. No insurance offered.
                    }
                }
            }
        }
    }
    if (phase==HIT) {
        if (hasHit) {
            hitTime+=deltaTime;
            if (hitTime>shuffleTime) {
                hasHit=false;
                hitTime=0.0;
                if (countValue(&playerHand)>21) {
                    phase=DEALER;
                } else {
                    phase=PLAYER;
                    if (this->isDouble) {
                        this->isDouble=false;
                        phase=DEALER;
                    }
                }
            }
        }
    }
    if (phase==DEALER) {
        if (!dealerStarted) {
            dealerStarted=true;
            dealerHand[1]->Flip();
            while (countValue(&dealerHand)<17) {
                dealerHand.emplace_back(*(deck.begin()));
                dealerHand.back()->Move(getX(dealerHand.size()), -0.3);
                dealerHand.back()->Flip();
                deck.erase(deck.begin());
            }
        } else {
            dealerTime+=deltaTime;
            if (dealerTime>shuffleTime) {
                dealerTime=0.0;
                dealerStarted=false;
                phase=COLLECTING;
            }
        }
    }
    if (phase==COLLECTING) {
        if (!startCollecting) {
            if (playerHand.size()==2 && countValue(&playerHand)==21 && countValue(&dealerHand)!=21) {
                winnerLabel->setText("Blackjack!");
            } else if (countValue(&playerHand)>21) {
                winnerLabel->setText("Dealer Wins!");
            } else if (countValue(&dealerHand)>21) {
                winnerLabel->setText("Player Wins!");
            } else if (countValue(&playerHand)>countValue(&dealerHand)) {
                winnerLabel->setText("Player Wins!");
            } else if (countValue(&playerHand)<countValue(&dealerHand)) {
                winnerLabel->setText("Dealer Wins!");
            } else {
                winnerLabel->setText("Push!");
            }
            for (auto &card : playerHand) {
                discard.push_back(card);
                card->Move(0.15/ (1280.0/720.0), 0);
                card->Flip();
            }
            for (auto &card : dealerHand) {
                discard.push_back(card);
                card->Move(0.15/ (1280.0/720.0), 0);
                card->Flip();
            }
            max=1000;
            startCollecting=true;
            playerHand.clear();
            dealerHand.clear();
        } else {
            collectTime+=deltaTime;
            if (collectTime>shuffleTime) {
                collectTime=0.0;
                if (discard.size()>=52*5) {
                    startCollecting=false;
                    max=5;
                    shuffleFinished=false;
                    shuffleStarted=false;
                    elapsedShuffleTime=0.0;
                    phase=SHUFFLE;
                } else {
                    startCollecting=false;
                    max=5;
                    phase=END;
                }
            }
        }
    }
    if (phase==END) {
        if (!isFirstRound && isWinner==false) {
            isWinner = true;
        }
    }
}
void Game::HandleInput(KeyFrame* frame) {
    if (KeyMonitor::getState(window, frame, ESCAPE) == PRESS) {
        this->nextState = menu;
    }
}
void Game::Enter() {
    std::cout << "Entering Game" << std::endl;
}
void Game::Exit() {
    std::cout << "Exiting Game" << std::endl;
    this->nextState = nullptr;
}
void Game::WindowSizeCallback(double width, double height) {
    exitButton->setWidth(width);
    exitButton->setHeight(height);
}
void Game::Click(double button, double x, double y) {
    exitButton->Click(button, x, y, this);
    hitButton->Click(button, x, y, this);
    standButton->Click(button, x, y, this);
    splitButton->Click(button, x, y, this);
    doubleButton->Click(button, x, y, this);
    insureButton->Click(button, x, y, this);
    dontInsureButton->Click(button, x, y, this);
    dealButton->Click(button, x, y, this);
}
void Game::Release(double button, double x, double y) {
    exitButton->Release(button, x, y, this);
    hitButton->Release(button, x, y, this);
    standButton->Release(button, x, y, this);
    splitButton->Release(button, x, y, this);
    doubleButton->Release(button, x, y, this);
    insureButton->Release(button, x, y, this);
    dontInsureButton->Release(button, x, y, this);
    dealButton->Release(button, x, y, this);
}
Gamestate *Game::getNextState() {
    return nextState;
}
Game::~Game() {
    delete exitButton;
    delete hitButton;
    delete standButton;
    delete splitButton;
    delete doubleButton;
    delete insureButton;
    delete dontInsureButton;
    delete dealButton;
    delete visualDistribution;
}