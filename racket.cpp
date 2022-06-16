#include "racket.hpp"
#include "game.hpp"
#include <algorithm>

using namespace sf;

#define MAX_SPEED 12.0f

Racket::Racket(sf::Vector2f position, sf::Vector2f size, Game& parent)
    : RectangleShape(size), Entity(position, {0, 0}, size), _parent(parent) {
    RectangleShape::setPosition(position);
}

void Racket::accelLeft() {
    _speed.x = std::max(-MAX_SPEED, _speed.x - MAX_SPEED / 10);
    isAccelerating = true;
}

void Racket::accelRight() {
    _speed.x = std::min(MAX_SPEED, _speed.x + MAX_SPEED / 10);
    isAccelerating = true;
}

void Racket::stopAccel() { isAccelerating = false; }

void Racket::move() {
    _pos += _speed;
    setPosition(_pos);
    // slowdown if not accelerating
    if (!isAccelerating) {
        if (std::abs(_speed.x) < 0.3) {
            _speed.x = 0;
        } else {
            _speed.x /= 4;
        }
    }
}

void Racket::collideWithBorders(sf::RenderWindow* window) {
    auto borders = window->getSize();
    auto size = getSize();

    if (_pos.x < 0) {
        _pos.x = 0;
        _speed.x = 0;
    }
    if (_pos.x > borders.x - size.x) {
        _pos.x = borders.x - size.x;
        _speed.x = 0;
    }
    RectangleShape::setPosition(_pos);
}

void Racket::adjustSize(int delta) {
    auto size = getSize();
    size.x += delta;
    // keep center in same place
    _pos.x -= float(delta) / 2;
    _bR.width = size.x;
    setSize(size);
}

void Racket::collideWith(Bonus::SpeedUp* bonus) { _parent.speedCallback(2); }
void Racket::collideWith(Bonus::SpeedDown* bonus) { _parent.speedCallback(-2); }
void Racket::collideWith(Bonus::Shield* bonus) { _parent.setBarrier(); }
void Racket::collideWith(Bonus::SizeUp* bonus) { adjustSize(10); }
void Racket::collideWith(Bonus::SizeDown* bonus) { adjustSize(10); }
void Racket::collideWith(Bonus::Sticky* bonus) { _isSticky = true; }
void Racket::collideWith(Bonus::Randomizer* bonus) { _parent.randomizerCallback(); }
void Racket::collideWith(Bonus::BallUp* bonus) {
    auto bounds = getTrueBounds();
    sf::Vector2f centerUp = {bounds.left + bounds.width, bounds.top};
    _parent.ballUpCallback(centerUp);
}
