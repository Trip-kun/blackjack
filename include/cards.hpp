#pragma once

#include "GL/Texture.hpp"
class Cards {
    Texture* backImage;
    Texture* aceOfClubs, *aceOfSpades, *aceOfHearts, *aceOfDiamonds, *twoOfClubs, *twoOfSpades, *twoOfHearts, *twoOfDiamonds, *threeOfClubs, *threeOfSpades, *threeOfHearts, *threeOfDiamonds, *fourOfClubs, *fourOfSpades, *fourOfHearts, *fourOfDiamonds, *fiveOfClubs, *fiveOfSpades, *fiveOfHearts, *fiveOfDiamonds, *sixOfClubs, *sixOfSpades, *sixOfHearts, *sixOfDiamonds, *sevenOfClubs, *sevenOfSpades, *sevenOfHearts, *sevenOfDiamonds, *eightOfClubs, *eightOfSpades, *eightOfHearts, *eightOfDiamonds, *nineOfClubs, *nineOfSpades, *nineOfHearts, *nineOfDiamonds, *tenOfClubs, *tenOfSpades, *tenOfHearts, *tenOfDiamonds, *jackOfClubs, *jackOfSpades, *jackOfHearts, *jackOfDiamonds, *queenOfClubs, *queenOfSpades, *queenOfHearts, *queenOfDiamonds, *kingOfClubs, *kingOfSpades, *kingOfHearts, *kingOfDiamonds;
    Cards() {
        backImage = new Texture("img/back.png");
        aceOfClubs = new Texture("img/ACE_CLUBS.png");
        aceOfSpades = new Texture("img/ACE_SPADES.png");
        aceOfHearts = new Texture("img/ACE_HEARTS.png");
        aceOfDiamonds = new Texture("img/ACE_DIAMONDS.png");
        twoOfClubs = new Texture("img/TWO_CLUBS.png");
        twoOfSpades = new Texture("img/TWO_SPADES.png");
        twoOfHearts = new Texture("img/TWO_HEARTS.png");
        twoOfDiamonds = new Texture("img/TWO_DIAMONDS.png");
        threeOfClubs = new Texture("img/THREE_CLUBS.png");
        threeOfSpades = new Texture("img/THREE_SPADES.png");
        threeOfHearts = new Texture("img/THREE_HEARTS.png");
        threeOfDiamonds = new Texture("img/THREE_DIAMONDS.png");
        fourOfClubs = new Texture("img/FOUR_CLUBS.png");
        fourOfSpades = new Texture("img/FOUR_SPADES.png");
        fourOfHearts = new Texture("img/FOUR_HEARTS.png");
        fourOfDiamonds = new Texture("img/FOUR_DIAMONDS.png");
        fiveOfClubs = new Texture("img/FIVE_CLUBS.png");
        fiveOfSpades = new Texture("img/FIVE_SPADES.png");
        fiveOfHearts = new Texture("img/FIVE_HEARTS.png");
        fiveOfDiamonds = new Texture("img/FIVE_DIAMONDS.png");
        sixOfClubs = new Texture("img/SIX_CLUBS.png");
        sixOfSpades = new Texture("img/SIX_SPADES.png");
        sixOfHearts = new Texture("img/SIX_HEARTS.png");
        sixOfDiamonds = new Texture("img/SIX_DIAMONDS.png");
        sevenOfClubs = new Texture("img/SEVEN_CLUBS.png");
        sevenOfSpades = new Texture("img/SEVEN_SPADES.png");
        sevenOfHearts = new Texture("img/SEVEN_HEARTS.png");
        sevenOfDiamonds = new Texture("img/SEVEN_DIAMONDS.png");
        eightOfClubs = new Texture("img/EIGHT_CLUBS.png");
        eightOfSpades = new Texture("img/EIGHT_SPADES.png");
        eightOfHearts = new Texture("img/EIGHT_HEARTS.png");
        eightOfDiamonds = new Texture("img/EIGHT_DIAMONDS.png");
        nineOfClubs = new Texture("img/NINE_CLUBS.png");
        nineOfSpades = new Texture("img/NINE_SPADES.png");
        nineOfHearts = new Texture("img/NINE_HEARTS.png");
        nineOfDiamonds = new Texture("img/NINE_DIAMONDS.png");
        tenOfClubs = new Texture("img/TEN_CLUBS.png");
        tenOfSpades = new Texture("img/TEN_SPADES.png");
        tenOfHearts = new Texture("img/TEN_HEARTS.png");
        tenOfDiamonds = new Texture("img/TEN_DIAMONDS.png");
        jackOfClubs = new Texture("img/JACK_CLUBS.png");
        jackOfSpades = new Texture("img/JACK_SPADES.png");
        jackOfHearts = new Texture("img/JACK_HEARTS.png");
        jackOfDiamonds = new Texture("img/JACK_DIAMONDS.png");
        queenOfClubs = new Texture("img/QUEEN_CLUBS.png");
        queenOfSpades = new Texture("img/QUEEN_SPADES.png");
        queenOfHearts = new Texture("img/QUEEN_HEARTS.png");
        queenOfDiamonds = new Texture("img/QUEEN_DIAMONDS.png");
        kingOfClubs = new Texture("img/KING_CLUBS.png");
        kingOfSpades = new Texture("img/KING_SPADES.png");
        kingOfHearts = new Texture("img/KING_HEARTS.png");
        kingOfDiamonds = new Texture("img/KING_DIAMONDS.png");
    }
public:
    ~Cards() {
        delete backImage;
        delete aceOfClubs;
        delete aceOfSpades;
        delete aceOfHearts;
        delete aceOfDiamonds;
        delete twoOfClubs;
        delete twoOfSpades;
        delete twoOfHearts;
        delete twoOfDiamonds;
        delete threeOfClubs;
        delete threeOfSpades;
        delete threeOfHearts;
        delete threeOfDiamonds;
        delete fourOfClubs;
        delete fourOfSpades;
        delete fourOfHearts;
        delete fourOfDiamonds;
        delete fiveOfClubs;
        delete fiveOfSpades;
        delete fiveOfHearts;
        delete fiveOfDiamonds;
        delete sixOfClubs;
        delete sixOfSpades;
        delete sixOfHearts;
        delete sixOfDiamonds;
        delete sevenOfClubs;
        delete sevenOfSpades;
        delete sevenOfHearts;
        delete sevenOfDiamonds;
        delete eightOfClubs;
        delete eightOfSpades;
        delete eightOfHearts;
        delete eightOfDiamonds;
        delete nineOfClubs;
        delete nineOfSpades;
        delete nineOfHearts;
        delete nineOfDiamonds;
        delete tenOfClubs;
        delete tenOfSpades;
        delete tenOfHearts;
        delete tenOfDiamonds;
        delete jackOfClubs;
        delete jackOfSpades;
        delete jackOfHearts;
        delete jackOfDiamonds;
        delete queenOfClubs;
        delete queenOfSpades;
        delete queenOfHearts;
        delete queenOfDiamonds;
        delete kingOfClubs;
        delete kingOfSpades;
        delete kingOfHearts;
        delete kingOfDiamonds;
    }
    static Cards* getCards() {
        static Cards* cards;
        if (cards==nullptr) {
            cards = new Cards();
        }
        return cards;
    }
    Texture* getBackImage() {
        return backImage;
    }
    Texture* getFrontFace(Card::Face face, Card::Suit suit) {
        int card = (face*4)+suit;
        switch (card) {
            case 0:
                return aceOfClubs;
            case 1:
                return aceOfSpades;
            case 2:
                return aceOfHearts;
            case 3:
                return aceOfDiamonds;
            case 4:
                return twoOfClubs;
            case 5:
                return twoOfSpades;
            case 6:
                return twoOfHearts;
            case 7:
                return twoOfDiamonds;
            case 8:
                return threeOfClubs;
            case 9:
                return threeOfSpades;
            case 10:
                return threeOfHearts;
            case 11:
                return threeOfDiamonds;
            case 12:
                return fourOfClubs;
            case 13:
                return fourOfSpades;
            case 14:
                return fourOfHearts;
            case 15:
                return fourOfDiamonds;
            case 16:
                return fiveOfClubs;
            case 17:
                return fiveOfSpades;
            case 18:
                return fiveOfHearts;
            case 19:
                return fiveOfDiamonds;
            case 20:
                return sixOfClubs;
            case 21:
                return sixOfSpades;
            case 22:
                return sixOfHearts;
            case 23:
                return sixOfDiamonds;
            case 24:
                return sevenOfClubs;
            case 25:
                return sevenOfSpades;
            case 26:
                return sevenOfHearts;
            case 27:
                return sevenOfDiamonds;
            case 28:
                return eightOfClubs;
            case 29:
                return eightOfSpades;
            case 30:
                return eightOfHearts;
            case 31:
                return eightOfDiamonds;
            case 32:
                return nineOfClubs;
            case 33:
                return nineOfSpades;
            case 34:
                return nineOfHearts;
            case 35:
                return nineOfDiamonds;
            case 36:
                return tenOfClubs;
            case 37:
                return tenOfSpades;
            case 38:
                return tenOfHearts;
            case 39:
                return tenOfDiamonds;
            case 40:
                return jackOfClubs;
            case 41:
                return jackOfSpades;
            case 42:
                return jackOfHearts;
            case 43:
                return jackOfDiamonds;
            case 44:
                return queenOfClubs;
            case 45:
                return queenOfSpades;
            case 46:
                return queenOfHearts;
            case 47:
                return queenOfDiamonds;
            case 48:
                return kingOfClubs;
            case 49:
                return kingOfSpades;
            case 50:
                return kingOfHearts;
            case 51:
                return kingOfDiamonds;
            default:
                std::cout << "Invalid Card" << std::endl;
                return nullptr;
        }
    }
};