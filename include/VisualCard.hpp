#pragma once
#include <chrono>
#include "Drawable.hpp"
#include "Image.hpp"
#include "Card.hpp"
class VisualCard : public Drawable {
public:
    enum flipAnim {
        FLIP, NONE, FLIPBACK
    };
    enum moveAnim {
        MOVE, STILL
    };
    static void setBackImage(Texture* texture);
    VisualCard(Card::Face face, Card::Suit suit, Texture* texture, GLProgram* program, float x, float y, float scale);
    void Draw(Context*) override;
    void Flip();
    void Move(double x, double y);
    flipAnim getFlipAnimation();
    moveAnim getMoveAnimation();
    ~VisualCard() override;
private:
    bool isBack = true;
    Image* image;
    Card::Face face{};
    Card::Suit suit{};
    double fullScale;
    static Texture* backImage;
    std::chrono::time_point<std::chrono::system_clock> startFlip, startMove;
    Texture* frontImage;
    const float width = 0.3/ (1280.0/720.0);
    const float height = 0.42;
    double xOffset=0;
    double yOffset=0;
    double goalX=0;
    double goalY=0;
    double startX;
    double startY;
    flipAnim flipAnimation = NONE;
    moveAnim moveAnimation = STILL;
};
