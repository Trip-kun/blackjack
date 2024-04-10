#pragma once

class Card {
public:
    enum Face {
        ACE, DUECE, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING
    };
    enum Suit {
        CLUBS, SPADES, HEARTS, DIAMONDS
    };
    Card(Suit suit, Face face) {
        this->suit=suit;
        this->face=face;
    }
    Face getFace() {
        return this->face;
    }
    Suit getSuit() {
        return this->suit;
    }
    virtual ~Card() = default;
protected:
    Face face;
    Suit suit;
};