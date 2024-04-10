#pragma once
#include <chrono>
#include "GL/Drawable.hpp"
#include "GL/Image.hpp"
#include "Card.hpp"
class VisualCard : public Drawable, public Card {
public:
    enum flipAnim {
        FLIP, NONE, FLIPBACK
    };
    enum moveAnim {
        MOVE, STILL
    };
    static void setBackImage(Texture* texture);
    VisualCard(Face face, Suit suit, Texture* texture, GLProgram* program, double x, double y, double scale);
    void Draw(Context*) override;
    void Flip();
    void Move(double x, double y);
    flipAnim getFlipAnimation();
    moveAnim getMoveAnimation();
    ~VisualCard() override;
private:
    bool isBack = true;
    Image* image;
    double fullScale;
    static Texture* backImage;
    std::chrono::time_point<std::chrono::system_clock> startFlip, startMove;
    Texture* frontImage;
    const double width = 0.3/ (1280.0/720.0);
    const double height = 0.42;
    double xOffset=0;
    double yOffset=0;
    double goalX=0;
    double goalY=0;
    double startX;
    double startY;
    flipAnim flipAnimation = NONE;
    moveAnim moveAnimation = STILL;
};
