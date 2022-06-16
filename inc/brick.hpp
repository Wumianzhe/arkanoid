#ifndef BRICK_H_
#define BRICK_H_

#include "entity.hpp"
#include <SFML/Graphics.hpp>
#include <array>

namespace Brick {
class Base : public Entity, public sf::RectangleShape {
  public:
    Base() = delete;
    Base(Base&) = delete;
    Base(Base&&) = delete;
    Base(sf::Vector2f pos, sf::Vector2f size);

    void move() override{};
    // prefer a callback, but don't know how to do it cleanly in time i have left
    virtual bool isDead() = 0;
    virtual bool hasBonus() { return false; }
    virtual int getBonusType() const { return -1; }
    virtual ~Base() = default;
};
class Normal : public Base {
  public:
    Normal(sf::Vector2f pos, sf::Vector2f size, int lives);
    void hitBy(Ball* ball) override;
    void hitBy(Racket* racket) override{};
    bool isDead() override;

  protected:
    void _reduceHealth();
    int _health;
};

class Bonus : public Normal {
  public:
    Bonus(sf::Vector2f pos, sf::Vector2f size, int type);
    int getBonusType() const override { return _type; }
    void hitBy(Ball* ball) override;
    void hitBy(Racket* racket) override{};
    bool hasBonus() override { return true; }

  private:
    int _type;
};

class Invuln : public Base {
  public:
    Invuln(sf::Vector2f pos, sf::Vector2f size);
    void hitBy(Ball* ball) override;
    void hitBy(Racket* racket) override{};
    bool isDead() override { return false; }
};

class Speed : public Normal {
  public:
    Speed(sf::Vector2f pos, sf::Vector2f size);
    void hitBy(Ball* ball) override;
    void hitBy(Racket* racket) override{};
};

// visual indication of health
static std::array<sf::Color, 6> colors = {sf::Color(192, 192, 192), sf::Color(115, 45, 15),  sf::Color(180, 180, 10),
                                          sf::Color(160, 170, 25),  sf::Color(10, 180, 100), sf::Color(10, 135, 180)};
} // namespace Brick

#endif // BRICK_H_
