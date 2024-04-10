#pragma once
#include <vector>
#include <ctime>
#include <random>
#include "Card.hpp"
class Deck {
    std::vector<Card*> internalDeck;
    std::vector<Card*> discard;
    std::default_random_engine generator;
public:
    explicit Deck(bool fill) {
        if (fill) {
            generator.seed(std::time(nullptr));
            for (int suit =0; suit<4; suit++) {
                for (int face =0; face<13; face++) {
                    internalDeck.push_back(new Card(static_cast<Card::Suit>(suit), static_cast<Card::Face>(face)));
                }
            }
            shuffle();
        }
    }
    Deck(Deck a, Deck b) {
        generator.seed(std::time(nullptr));
        for (Card* c : a.internalDeck) {
            internalDeck.push_back(c);
        }
        for (Card* c : b.internalDeck) {
            internalDeck.push_back(c);
        }
        shuffle();
    }
    void shuffle() {
        for (Card* c : discard) {
            internalDeck.push_back(c);
        }
        discard.clear();
        std::uniform_int_distribution<unsigned long> distribution(0, internalDeck.size()-1);
        for (int _ = 0; _<internalDeck.size(); _++) {
            for (std::vector<Card*>::iterator it = internalDeck.begin(); it<internalDeck.end(); ++it) {
                auto it2 = internalDeck.begin() + distribution(generator);
                //std::cout << "Swapping: " << it->getFace() << " Of " << it->getSuit() << " with " << it2->getFace() << " Of " << it2->getSuit() << std::endl;
                std::iter_swap(it, it2);
            }
        }
    }
    Card* pull() {
        Card* c = internalDeck.back();
        internalDeck.pop_back();
        return c;
    }
    void put(Card* c) {
        discard.push_back(c);
    }
    void printAll() {
        std::cout << "Deck: " << std::endl;
        for (Card* c : internalDeck) {
            std::cout << c->getFace() << " Of " << c->getSuit() << std::endl;
        }
        std::cout << "Discard: " << std::endl;

        for (Card* c : discard) {
            std::cout << c->getFace() << " Of " << c->getSuit() << std::endl;
        }
    }
};