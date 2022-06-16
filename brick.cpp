#include "brick.hpp"
#include "ball.hpp"

using namespace Brick;

Base::Base(sf::Vector2f pos, sf::Vector2f size) : Entity(pos, {0, 0}, size), sf::RectangleShape(size) {
    setPosition(pos);
}

Normal::Normal(sf::Vector2f pos, sf::Vector2f size, int lives) : Base(pos, size) {
    _health = lives;
    setFillColor(colors[lives]);
}
void Normal::_reduceHealth() {
    _health--;
    if (_health > 0) {
        setFillColor(colors[_health]);
    }
}

void Normal::hitBy(Ball* ball) {
    _reduceHealth();
    ball->collideWith(this);
}
void Brick::Bonus::hitBy(Ball* ball) {
    _reduceHealth();
    ball->collideWith(this);
}

Brick::Bonus::Bonus(sf::Vector2f pos, sf::Vector2f size, int type) : Normal(pos, size, 2) { _type = type; }

Speed::Speed(sf::Vector2f pos, sf::Vector2f size, int lives) : Normal(pos, size, lives) {}

void Speed::hitBy(Ball* ball) {
    _reduceHealth();
    ball->collideWith(this);
}

Invuln::Invuln(sf::Vector2f pos, sf::Vector2f size) : Base(pos, size) {}

void Invuln::hitBy(Ball* ball) { ball->collideWith(this); }
