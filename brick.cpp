#include "brick.hpp"
#include "ball.hpp"

using namespace Brick;

const int DefaultHealth = 2;

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

bool Normal::isDead() { return _health < 1; }

void Normal::hitBy(Ball* ball) {
    _reduceHealth();
    ball->collideWith(this);
}
void Brick::Bonus::hitBy(Ball* ball) {
    _reduceHealth();
    ball->collideWith(this);
}

Brick::Bonus::Bonus(sf::Vector2f pos, sf::Vector2f size, int type) : Normal(pos, size, DefaultHealth) { _type = type; }

Speed::Speed(sf::Vector2f pos, sf::Vector2f size) : Normal(pos, size, DefaultHealth) {}

void Speed::hitBy(Ball* ball) {
    _reduceHealth();
    ball->collideWith(this);
}

Invuln::Invuln(sf::Vector2f pos, sf::Vector2f size) : Base(pos, size) { setFillColor(colors[0]); }

void Invuln::hitBy(Ball* ball) { ball->collideWith(this); }
