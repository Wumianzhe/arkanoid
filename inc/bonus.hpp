#ifndef BONUS_H_
#define BONUS_H_

#include "declarations.hpp"
#include "entity.hpp"
#include <SFML/Graphics.hpp>
#include <array>

namespace Bonus {
enum type {
    SPEED_UP = 0,
    SPEED_DOWN = 1,
    SHIELD = 2,
    SIZE_UP = 3,
    SIZE_DOWN = 4,
    STICKY = 5,
    RANDOMIZER = 6,
    BALL_UP = 7
};
static std::array<sf::Color, 8> colors = {sf::Color(255, 0, 0), sf::Color(0, 0, 255),   sf::Color(255, 0, 255),
                                          sf::Color(0, 255, 0), sf::Color(128, 128, 0), sf::Color(0, 192, 0),
                                          sf::Color(192, 0, 0), sf::Color(0, 0, 192)};
class Base : public Entity, public sf::CircleShape {
  public:
    Base(sf::Vector2f pos) : Entity(pos, {0, 5}, {10, 10}), CircleShape(5, 8) { setPosition(pos); };
    void move() override { sf::CircleShape::move(_speed); }
};
class SpeedUp : public Base {
  public:
    SpeedUp(sf::Vector2f pos) : Base(pos) { setFillColor(Bonus::colors[0]); }
    void hitBy(Racket* racket) override;
    void hitBy(Ball* ball) override {}
};
class SpeedDown : public Base {
  public:
    SpeedDown(sf::Vector2f pos) : Base(pos) { setFillColor(Bonus::colors[1]); }
    void hitBy(Racket* racket) override;
    void hitBy(Ball* ball) override {}
};
class Shield : public Base {
  public:
    Shield(sf::Vector2f pos) : Base(pos) { setFillColor(Bonus::colors[2]); }
    void hitBy(Racket* racket) override;
    void hitBy(Ball* ball) override {}
};
class SizeUp : public Base {
  public:
    SizeUp(sf::Vector2f pos) : Base(pos) { setFillColor(Bonus::colors[3]); }
    void hitBy(Racket* racket) override;
    void hitBy(Ball* ball) override {}
};
class SizeDown : public Base {
  public:
    SizeDown(sf::Vector2f pos) : Base(pos) { setFillColor(Bonus::colors[4]); }
    void hitBy(Racket* racket) override;
    void hitBy(Ball* ball) override {}
};
class Sticky : public Base {
  public:
    Sticky(sf::Vector2f pos) : Base(pos) { setFillColor(Bonus::colors[5]); }
    void hitBy(Racket* racket) override;
    void hitBy(Ball* ball) override {}
};
class Randomizer : public Base {
  public:
    Randomizer(sf::Vector2f pos) : Base(pos) { setFillColor(Bonus::colors[6]); }
    void hitBy(Racket* racket) override;
    void hitBy(Ball* ball) override {}
};
class BallUp : public Base {
  public:
    BallUp(sf::Vector2f pos) : Base(pos) { setFillColor(Bonus::colors[7]); }
    void hitBy(Racket* racket) override;
    void hitBy(Ball* ball) override {}
};
} // namespace Bonus

#endif // BONUS_H_
