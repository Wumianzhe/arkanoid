#ifndef RACKET_H_
#define RACKET_H_

#include "ball.hpp"
#include "collision.hpp"
#include "entity.hpp"
#include <SFML/Graphics.hpp>

class Racket : public Entity, public sf::RectangleShape, public collision::Actor {
  public:
    Racket() = delete;
    Racket(sf::Vector2f position, sf::Vector2f size, Game& parent);
    void move() override;
    void accelLeft();
    void accelRight();
    void stopAccel();
    void adjustSize(int delta);

    void hitBy(Ball* ball) override {
        ball->collideWith(this);
        _isSticky = false;
    }
    void hitBy(Racket* racket) override{};
    void collideWith(Brick::Normal* brick) override {}
    void collideWith(Brick::Bonus* brick) override {}
    void collideWith(Brick::Invuln* brick) override {}
    void collideWith(Brick::Speed* brick) override {}
    void collideWith(Bonus::SpeedUp* bonus) override;
    void collideWith(Bonus::SpeedDown* bonus) override;
    void collideWith(Bonus::Shield* bonus) override;
    void collideWith(Bonus::SizeUp* bonus) override;
    void collideWith(Bonus::SizeDown* bonus) override;
    void collideWith(Bonus::Sticky* bonus) override;
    void collideWith(Bonus::Randomizer* bonus) override;
    void collideWith(Bonus::BallUp* bonus) override;
    void collideWithBorders(sf::RenderWindow* window) override;

    bool isSticky() { return _isSticky; };

  private:
    bool isAccelerating = false;
    bool _isSticky = false;
    Game& _parent;
};

#endif // RACKET_H_
