#ifndef RACKET_H_
#define RACKET_H_

#include "ball.hpp"
#include "collision.hpp"
#include "entity.hpp"
#include <SFML/Graphics.hpp>

class Racket : public Entity, public sf::RectangleShape, public collision::Actor {
  public:
    Racket() = delete;
    Racket(sf::Vector2f position, sf::Vector2f size);
    void move() override;
    void accelLeft();
    void accelRight();
    void stopAccel();

    void hitBy(Ball* ball) override { ball->collideWith(this); }
    void collideWith(Brick::Normal* brick) override {}
    void collideWith(Brick::Bonus* brick) override {}
    void collideWith(Brick::Invuln* brick) override {}
    void collideWith(Brick::Speed* brick) override {}
    void collideWith(Bonus* bonus) override;
    void collideWithBorders(sf::RenderWindow* window) override;

    bool isSticky() { return _isSticky; };

  private:
    bool isAccelerating = false;
    bool _isSticky = false;
};

#endif // RACKET_H_
