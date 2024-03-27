#pragma once

class Card {
public:
    enum Face {
        ACE, DUECE, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING
    };
    enum Suit {
        HEARTS, DIAMONDS, CLUBS, SPADES
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
private:
    Face face;
    Suit suit;
};