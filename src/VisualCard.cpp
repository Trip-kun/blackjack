#include "VisualCard.hpp"

#include <map>
#include <unordered_map>
#include <vector>

#include "tween.hpp"
Texture* VisualCard::backImage = nullptr;
void VisualCard::setBackImage(Texture* texture) {
    backImage = texture;
}
VisualCard::VisualCard(Face face, Suit suit, Texture *texture, GLProgram* program, double x, double y,  double scale): Card(suit, face) {
    this->face=face;
    this->suit=suit;
    this->frontImage=texture;
    this->fullScale=scale;
    this->startX = x;
    this->startY = y;
    this->image = getCacheImage({x, y, width*scale, height*scale}, program, Card(suit, face), false);
}
Image* VisualCard::getCacheImage(Position pos, GLProgram* program, Card card, bool del) {
    static std::vector<Image*> cache(52);
    int c = (card.getFace()*4)+card.getSuit();
    if (cache[c]==nullptr) {
        cache[c] = new Image(backImage, program, pos);
    }
    if (del) {
        for (int it = 0; it<cache.size(); it++) {
            if (cache[it]!=nullptr) {
                delete cache[it];
                cache[it]=nullptr;
            }
        }
        return nullptr;
    }
    return cache[c];
}
void VisualCard::Draw(Context* ctx) {
    std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
    double flipScale = 1;
    double flipOffset = 0;
    double moveScale = 1;
    double moveOffsetX = 0;
    double moveOffsetY = 0;
    switch (this->flipAnimation) {
        case NONE: {
            break;
        }
        case FLIP: {
            std::chrono::duration<double> elapsed = now-startFlip;
            flipScale = tween::linear(elapsed.count(), 1.0, 0.0, 0.25);
            flipOffset = tween::linear(elapsed.count(), 0.0, this->height*this->fullScale/2, 0.25);
            if (flipScale==0) {
                isBack=!isBack;
                startFlip=std::chrono::system_clock::now();
                this->flipAnimation=FLIPBACK;
            }
            break;
        }
        case FLIPBACK: {
            std::chrono::duration<double> elapsed = now-startFlip;
            flipScale = tween::linear(elapsed.count(), 0.0, 1.0, 0.25);
            flipOffset = tween::linear(elapsed.count(), this->height*this->fullScale/2, 0.0, 0.25);
            if (flipScale==0) {
                isBack=!isBack;
                this->flipAnimation=NONE;
            }
            break;
        }
    }
    switch (this->moveAnimation) {
        case STILL: {
            moveOffsetX = xOffset;
            moveOffsetY = yOffset;
            break;
        }
        case MOVE: {
            std::chrono::duration<double> elapsed = now-startMove;
            xOffset=tween::easeInQuad(elapsed.count(), startX, goalX, 0.5);
            yOffset=tween::easeOutQuad(elapsed.count(), startY, goalY, 0.5);
            if (elapsed.count()>0.5) {
                this->moveAnimation=STILL;
            }
            moveOffsetX = xOffset;
            moveOffsetY = yOffset;
            break;
        }
    }
    image->setOffset(moveOffsetX, moveOffsetY+flipOffset);
    image->setTransform({ moveScale, flipScale, 0});
    if (isBack) {
        image->setTexture(backImage);
    } else {
        image->setTexture(frontImage);
    }
    image->Draw(ctx);
}
void VisualCard::Flip() {
    this->flipAnimation=FLIP;
    this->startFlip=std::chrono::system_clock::now();
}
void VisualCard::Move(double x, double y) {
    goalX=x;
    goalY=y;
    startX = xOffset;
    startY = yOffset;
    startMove=std::chrono::system_clock::now();
    this->moveAnimation=MOVE;
}

VisualCard::~VisualCard() = default;
void VisualCard::Clean() {
    getCacheImage({0, 0, 0, 0}, nullptr, Card(CLUBS, ACE), true);
}

VisualCard::flipAnim VisualCard::getFlipAnimation() {
    return flipAnimation;
}
VisualCard::moveAnim VisualCard::getMoveAnimation() {
    return moveAnimation;
}