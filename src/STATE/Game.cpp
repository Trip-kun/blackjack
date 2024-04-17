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
double getSplitX(int count, bool isLeft) {
    double out = getX(count);
    if (isLeft) {
        return out-0.5;
    }
    return out+0.5;
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
    deckD.clean();
    deckC.clean();
    this->exitButton = new HexicImageButton<Game*>(basicProgram, textProgram, fonts, "Exit Game!", {-1, 0.9, 1.0/3.0, 0.1}, {1, 1, 1});
    exitButton->onClick([](Game *game) {
        game->nextState=game->menu;
    });
    this-> hitButton = new HexicImageButton<Game*>(basicProgram, textProgram, fonts, "Hit", {-1, -1, 1.0/3.0, 0.1}, {1, 1, 1});
    this->hitButton->onClick([](Game *game) {
        if (game->phase==PLAYER && !game->hasHit) {
            if (!game->isSplit) {
                game->playerHand.emplace_back(*(game->deck.begin()));
                game->playerHand.back()->Move(getX(game->playerHand.size()), -0.9);
                game->playerHand.back()->Flip();
            } else {
                if (game->split_phase==LEFT) {
                    game->splitHand.emplace_back(*(game->deck.begin()));
                    game->splitHand.back()->Move(getSplitX(game->splitHand.size(), true), -0.9);
                    game->splitHand.back()->Flip();
                } else {
                    game->playerHand.emplace_back(*(game->deck.begin()));
                    game->playerHand.back()->Move(getSplitX(game->playerHand.size(), false), -0.9);
                    game->playerHand.back()->Flip();
                }
            }
            game->deck.erase(game->deck.begin());
            game->hasHit=true;
            game->phase=HIT;
        }
    });
    this-> standButton = new HexicImageButton<Game*>(basicProgram, textProgram, fonts, "Stand", {-(2.0/3.0), -1, 1.0/3.0, 0.1}, {1, 1, 1});
    this->standButton->onClick([](Game *game) {
        if (game->phase==PLAYER) {

            game->phase=DEALER;
            if (game->split_phase==LEFT) {
                game->split_phase=RIGHT;
                game->phase = PLAYER;
            }
        }
    });
    this-> splitButton = new HexicImageButton<Game*>(basicProgram, textProgram, fonts, "Split", {-(1.0/3.0), -1, 1.0/3.0, 0.1}, {1, 1, 1});
    this->splitButton->onClick([](Game *game) {
        if (game->phase==PLAYER && game->split_phase==NONE && game->playerHand.size()==2) {
            if (game->playerHand[0]->getFace()==game->playerHand[1]->getFace()) {
                if (game->bet>game->balance) {
                    game->highBetSource=DOUBLE;
                    game->phase=HIGHBET;
                    return;
                }
                game->balance-=game->bet;
                game->splitHand.emplace_back(game->playerHand[1]);
                game->playerHand.pop_back();
                game->splitHand[0]->Move(getSplitX(1, true), -0.9);
                game->playerHand[0]->Move(getSplitX(1, false), -0.9);

                game->playerHand.emplace_back(*(game->deck.begin()));
                game->deck.erase(game->deck.begin());
                game->playerHand.back()->Flip();
                game->splitHand.emplace_back(*(game->deck.begin()));
                game->deck.erase(game->deck.begin());
                game->splitHand.back()->Flip();
                game->playerHand.back()->Move(getSplitX(2, false), -0.9);
                game->splitHand.back()->Move(getSplitX(2, true), -0.9);
                game->isSplit=true;
                game->phase=SPLIT;
            }
        }
    });
    this-> doubleButton = new HexicImageButton<Game*>(basicProgram, textProgram, fonts, "Double", {0, -1, 1.0/3.0, 0.1}, {1, 1, 1});
    this->doubleButton->onClick([](Game *game) {
        if (game->phase==PLAYER && (game->split_phase==LEFT ? game->splitHand.size() : game->playerHand.size())==2) {
            if (game->bet>game->balance) {
                game->highBetSource=DOUBLE;
                game->phase=HIGHBET;
                return;
            }
            game->balance-=game->bet;
            if (!game->isSplit) {
                game->playerHand.emplace_back(*(game->deck.begin()));
                game->playerHand.back()->Move(getX(game->playerHand.size()), -0.9);
                game->playerHand.back()->Flip();
                game->rightDoubled=true;
            } else {
                if (game->split_phase==LEFT) {
                    game->splitHand.emplace_back(*(game->deck.begin()));
                    game->splitHand.back()->Move(getSplitX(game->splitHand.size(), true), -0.9);
                    game->splitHand.back()->Flip();
                    game->leftDoubled=true;
                } else {
                    game->playerHand.emplace_back(*(game->deck.begin()));
                    game->playerHand.back()->Move(getSplitX(game->playerHand.size(), false), -0.9);
                    game->playerHand.back()->Flip();
                    game->rightDoubled=true;
                }
            }
            game->deck.erase(game->deck.begin());
            game->hasHit=true;
            game->isDouble=true;
            game->phase=HIT;
        }
    });
    this-> insureButton = new HexicImageButton<Game*>(basicProgram, textProgram, fonts, "Insure", {(1.0/3.0), -1, 1.0/3.0, 0.1}, {1, 1, 1});
    this->insureButton->onClick([](Game *game) {
        if (game->phase==PLAYER_INSURE) {
            if (game->bet/2>game->balance) {
                game->highBetSource=INSURANCE;
                game->phase=HIGHBET;
                return;
            }
            game->balance-=game->bet/2;
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
            if (countValue(&game->dealerHand)==21) {
                game->phase=DEALER;
            }
        }
    });
    this-> dealButton = new HexicImageButton<Game*>(basicProgram, textProgram, fonts, "Deal", {(2.0/3.0), -1, 1.0/3.0, 0.1}, {1, 1, 1});
    this->dealButton->onClick([](Game *game) {
        if (game->phase==END) {
            game->hasInsured=false;
            game->isFirstRound=false;
            if (game->bet>game->balance) {
                game->highBetSource=START;
                game->phase=HIGHBET;
                return;
            }
            game->leftDoubled=false;
            game->rightDoubled=false;
            game->balance-=game->bet;
            game->isDouble=false;
            game->phase=DEALING;
        }
    });
    winnerLabel = new HexicImageButton<Game*>(textProgram, textProgram, fonts, "", {-0.5, 0.5, 1.0/3.0, 0.1}, {1, 1, 1});
    splitLabel = new HexicImageButton<Game*>(textProgram, textProgram, fonts, "", {-0.5, 0.6, 1.0/3.0, 0.1}, {1, 1, 1});
    balanceLabel = new HexicImageButton<Game*>(textProgram, textProgram, fonts, "Balance: $1000", {-0.5, 0.7, 1.0/3.0, 0.1}, {1, 1, 1});
    betLabel = new HexicImageButton<Game*>(textProgram, textProgram, fonts, "Bet (Min $2): $20", {-0.5, 0.8, 1.0/3.0, 0.1}, {1, 1, 1});
    incrementBet = new HexicImageButton<Game*>(basicProgram, textProgram, fonts, "+", {0, 0.8, 1.0/3.0, 0.1}, {1, 1, 1});
    this->incrementBet->onClick([](Game *game) {
        if (game->phase==END) {
            if (game->bet+2<=game->balance) {
                game->bet+=2;
                game->betLabel->setText((std::string("Bet (Min $2): $") + std::to_string(game->bet)).c_str());
            }
        }
    });
    decrementBet = new HexicImageButton<Game*>(basicProgram, textProgram, fonts, "-", {-1, 0.8, 1.0/3.0, 0.1}, {1, 1, 1});
    this->decrementBet->onClick([](Game *game) {
        if (game->phase==END) {
            if (game->bet-2>0) {
                game->bet-=2;
                game->betLabel->setText((std::string("Bet (Min $2): $") + std::to_string(game->bet)).c_str());
            }
        }
    });
    highBetLabel = new HexicImageButton<Game*>(textProgram, textProgram, fonts, "You can't afford that bet!", {-0.5, 0.4, 1.0/3.0, 0.1}, {1, 1, 1});
    restartButton = new HexicImageButton<Game*>(basicProgram, textProgram, fonts, "Restart", {-0.5, 0.4, 1.0/3.0, 0.1}, {1, 1, 1});
    this->restartButton->onClick([](Game *game) {
        if (game->phase==LOSE) {
            game->balance=1000;
            game->bet=20;
            game->elapsedShuffleTime=0.0;
            game->shuffleFinished=false;
            game->shuffleStarted=false;
            game->phase=SHUFFLE;
        }
    });
    okayButton = new HexicImageButton<Game*>(basicProgram, textProgram, fonts, "Okay", {0, 0.4, 1.0/3.0, 0.1}, {1, 1, 1});
    this->okayButton->onClick([](Game *game) {
        if (game->phase==HIGHBET) {
            if (game->highBetSource==START) {
                game->phase=COLLECTING;
            }
            if (game->highBetSource==DOUBLE) {
                game->phase=PLAYER;
            }
            if (game->highBetSource==INSURANCE) {
                game->phase=PLAYER;
            }
        }
    });
}
void Game::Render(Context *ctx) {
    glClearColor((53.0f/255.0f), (101.0f/255.0f), (77.0f/255.0f), 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    for (auto it = deck.rbegin(); it!=deck.rend(); it++) {
        (*it)->Draw(ctx);
        //if (c++>this->max) break;
    }
    for (auto it = discard.rbegin(); it!=discard.rend(); it++) {
        (*it)->Draw(ctx);
        //if (c++>this->max) break;
    }
    for (auto &card : playerHand) {
        card->Draw(ctx);
    }
    for (auto &card : dealerHand) {
        card->Draw(ctx);
    }
    for (auto &card : splitHand) {
        card->Draw(ctx);
    }
    exitButton->Draw(ctx);
    balanceLabel->setText((std::string("Balance: $") + std::to_string(balance)).c_str());
    balanceLabel->Draw(ctx);
    betLabel->setText((std::string("Bet (Min $2): $") + std::to_string(bet)).c_str());
    betLabel->Draw(ctx);
    if (phase==PLAYER) {
        hitButton->Draw(ctx);
        standButton->Draw(ctx);
        if (playerHand.size()==2) {
            doubleButton->Draw(ctx);
            if (playerHand[0]->getFace()==playerHand[1]->getFace() && !isSplit)
                splitButton->Draw(ctx);
        }
        if (split_phase!=NONE) {
            if (split_phase==LEFT) {
                splitLabel->setText("Left");
            } else {
                splitLabel->setText("Right");
            }
            splitLabel->Draw(ctx);
        }
    }
    if (phase==HIGHBET) {
        highBetLabel->Draw(ctx);
        okayButton->Draw(ctx);
    }
    if (phase==LOSE) {
        restartButton->Draw(ctx);
    }
    if (phase==PLAYER_INSURE) {
        insureButton->Draw(ctx);
        dontInsureButton->Draw(ctx);
    }
    if (phase==END) {
        dealButton->Draw(ctx);
        incrementBet->Draw(ctx);
        decrementBet->Draw(ctx);
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
            this->isSplit=false;
            this->split_phase=NONE;
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
    if (phase==HIT)  {
        if (hasHit) {
            hitTime+=deltaTime;
            if (hitTime>shuffleTime) {
                std::vector<VisualCard*>* hand;
                if (!isSplit) {
                    hand=&playerHand;
                } else {
                    if (split_phase==LEFT) {
                        hand=&splitHand;
                    } else {
                        hand=&playerHand;
                    }
                }
                hasHit=false;
                hitTime=0.0;
                if (countValue(hand)>21) {
                    this->isDouble=false;
                    phase=DEALER;
                    if (this->isSplit) {
                        if (split_phase==LEFT) {
                            split_phase=RIGHT;
                            phase = PLAYER;
                        }
                    }
                } else {
                    phase=PLAYER;
                    if (this->isDouble) {
                        this->isDouble=false;
                        phase=DEALER;
                        if (split_phase==LEFT) {
                            split_phase=RIGHT;
                            phase = PLAYER;
                        }
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
            if (!isSplit) {
                if (playerHand.size()==2 && countValue(&playerHand)==21 && (countValue(&dealerHand)!=21 || dealerHand.size()>2)) {
                    balance+=bet*2.5 * (this->rightDoubled ? 2 : 1);
                    winnerLabel->setText("Blackjack!");
                } else if (countValue(&playerHand)>21) {
                    winnerLabel->setText("Dealer Wins!");
                } else if (countValue(&dealerHand)>21) {
                    balance+=bet*2* (this->rightDoubled ? 2 : 1);
                    winnerLabel->setText("Player Wins!");
                } else if (countValue(&playerHand)>countValue(&dealerHand)) {
                    balance+=2*bet* (this->rightDoubled ? 2 : 1);
                    winnerLabel->setText("Player Wins!");
                } else if (countValue(&playerHand)<countValue(&dealerHand)) {
                    winnerLabel->setText("Dealer Wins!");
                } else {
                    balance+=bet* (this->rightDoubled ? 2 : 1);
                    winnerLabel->setText("Push!");
                }
            } else
                {
                std::string winner1;
                std::string winner2;
                if (playerHand.size()==2 && countValue(&playerHand)==21 && (countValue(&dealerHand)!=21 || dealerHand.size()>2)) {
                    this->balance+=bet*2.5* (this->rightDoubled ? 2 : 1);
                    winner1="Player Blackjack!";
                } else if (countValue(&playerHand)>21) {
                    winner1="Dealer Wins!";
                } else if (countValue(&dealerHand)>21) {
                    this->balance+=bet*2* (this->rightDoubled ? 2 : 1);
                    winner1="Player Wins!";
                } else if (countValue(&playerHand)>countValue(&dealerHand)) {
                    this->balance+=2*bet* (this->rightDoubled ? 2 : 1);
                    winner1="Player Wins!";
                } else if (countValue(&playerHand)<countValue(&dealerHand)) {
                    winner1="Dealer Wins!";
                } else {
                    this->balance+=bet* (this->rightDoubled ? 2 : 1);
                    winner1="Push!";
                }
                if (splitHand.size()==2 &&countValue(&splitHand)==21 &&  (countValue(&dealerHand)!=21 || dealerHand.size()>2)) {
                    this->balance+=2.5*bet* (this->leftDoubled ? 2 : 1);
                    winner2="Player Blackjack!";
                } else if (countValue(&splitHand)>21) {
                    winner2="Dealer Wins!";
                } else if (countValue(&dealerHand)>21) {
                    this->balance+=2*bet* (this->leftDoubled ? 2 : 1);
                    winner2="Player Wins!";
                } else if (countValue(&splitHand)>countValue(&dealerHand)) {
                    this->balance+=2*bet* (this->leftDoubled ? 2 : 1);
                    winner2="Player Wins!";
                } else if (countValue(&splitHand)<countValue(&dealerHand)) {
                    winner2="Dealer Wins!";
                } else {
                    this->balance+=bet* (this->leftDoubled ? 2 : 1);
                    winner2="Push!";
                }
                if (this->hasInsured) {
                    if (countValue(&dealerHand)==21 && dealerHand.size()==2) {
                        this->balance+=3*bet/2;
                    }
                }
                winnerLabel->setText((std::string("Left: ") + winner2 + std::string("\nRight: ") + winner1).c_str());
            }
            for (auto &card : playerHand) {
                discard.push_back(card);
                card->Move(0.15/ (1280.0/720.0), 0);
                card->Flip();
            }
            for (auto &card : splitHand) {
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
            splitHand.clear();
            dealerHand.clear();
        } else {
            collectTime+=deltaTime;
            if (collectTime>shuffleTime) {
                collectTime=0.0;
                if (balance<2) {
                    phase=LOSE;
                    return;
                }
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
    if (phase==SPLIT) {
        splitTimer+=deltaTime;
        if (splitTimer>shuffleTime) {
            splitTimer=0.0;
            phase=PLAYER;
            split_phase = LEFT;
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
    incrementBet->Click(button, x, y, this);
    decrementBet->Click(button, x, y, this);
    restartButton->Click(button, x, y, this);
    okayButton->Click(button, x, y, this);
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
    incrementBet->Release(button, x, y, this);
    decrementBet->Release(button, x, y, this);
    restartButton->Release(button, x, y, this);
    okayButton->Release(button, x, y, this);
}
Gamestate *Game::getNextState() {
    return nextState;
}
Game::~Game() {
    for (auto &card : playerHand) {
        delete card;
    }
    for (auto &card : dealerHand) {
        delete card;
    }
    for (auto &card : splitHand) {
        delete card;
    }
    for (auto &card : deck) {
        delete card;
    }
    for (auto &card : discard) {
        delete card;
    }
    delete exitButton;
    delete hitButton;
    delete standButton;
    delete splitButton;
    delete doubleButton;
    delete insureButton;
    delete dontInsureButton;
    delete dealButton;
    delete visualDistribution;
    delete winnerLabel;
    delete splitLabel;
    delete balanceLabel;
    delete betLabel;
    delete incrementBet;
    delete decrementBet;
    delete highBetLabel;
    delete restartButton;
    delete okayButton;
    VisualCard::Clean();
}