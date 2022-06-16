#include "ball.hpp"
#include "functions.hpp"
#include "racket.hpp"
#include <cmath>
#include <iostream>

using namespace std;

Ball::Ball(sf::Vector2f position, float radius)
    : sf::CircleShape(radius), Entity(position, {0, 0}, {2 * radius, 2 * radius}) {
    CircleShape::setPosition(position);
    _speed = {0, 8};
}
void Ball::move() {
    _pos += _speed;
    setPosition(_pos);
}

void Ball::move(sf::Vector2f speed) {
    _pos += speed;
    setPosition(_pos);
}
void Ball::collideWithBorders(sf::RenderWindow* window) {
    auto borders = window->getSize();
    float size = getRadius() * 2;
    if (_pos.x < 0) {
        _pos.x = -_pos.x;
        _speed.x = -_speed.x;
    }
    if (_pos.y < 0) {
        _pos.y = -_pos.y;
        _speed.y = -_speed.y;
    }
    if (_pos.x + size > borders.x) {
        _pos.x = borders.x - (_pos.x - borders.x);
        _speed.x = -_speed.x;
    }
    if (_pos.y + size > borders.y) {
        _pos.y = borders.y - (_pos.y - borders.y);
        _speed.y = -_speed.y;
    }
    CircleShape::setPosition(_pos);
}

bool Ball::contains(sf::Vector2f point) const {
    float radius = getRadius();
    return normSq(point - _pos) <= radius * radius;
}
bool Ball::_collidesWithRect(sf::FloatRect bounds) const {
    sf::FloatRect _bounds = getTrueBounds();
    sf::Vector2f topLeft = {bounds.left, bounds.top};
    sf::Vector2f sizes = {bounds.width, bounds.height};
    int sides = sideIntersect(bounds, _bounds);
    if (!sides) {
        return false;
    }

    // if intersection is on one side, it is correct, but corners need to be rechecked
    if (sides & side::left && sides & side::top) {
        // corner is outside circle
        if (!contains(topLeft)) {
            return false;
        }
    }
    if (sides & side::right && sides & side::top) {
        if (!contains(topLeft + sf::Vector2f{sizes.x, 0})) {
            return false;
        }
    }
    if (sides & side::left && sides & side::bottom) {
        if (!contains(topLeft + sf::Vector2f{0, sizes.y})) {
            return false;
        }
    }
    if (sides & side::right && sides & side::bottom) {
        if (!contains(topLeft + sf::Vector2f{sizes.x, sizes.y})) {
            return false;
        }
    }
    return true;
}

void Ball::collideWith(Racket* racket) {
    if (!_collidesWithRect(racket->getTrueBounds())) {
        return;
    }

    int boxIntersect = intersects(racket);
    sf::Vector2f racketSize = racket->getSize();
    sf::Vector2f racketPos = racket->getPosition();
    float radius = getRadius();
    float dt = 0;

    // simulating ball trajectory in continuous time
    _pos = _pos - _speed;
    if (boxIntersect & side::top) {
        // how much of tick is left after hitting boundary
        dt = 1 - (racketPos.y - _pos.y - 2 * radius) / _speed.y;
    }
    if (boxIntersect & side::left) {
        dt = 1 - (racketPos.x - _pos.x) / _speed.x;
    }
    if (boxIntersect & side::right) {
        dt = 1 - (racketPos.x + racketSize.x - _pos.x) / _speed.x;
    }
    _pos += (1 - dt) * _speed;

    auto center = racketPos + racketSize / 2.0f;
    sf::Vector2f angle = (_pos - center) / float(sqrt(normSq(_pos - center)));
    float speed = sqrt(normSq(_speed));
    _speed = angle * speed;
    setPosition(_pos);
}

void Ball::launch(Racket* racket) {
    onRacket = false;
    _pos.y += 1;
    collideWith(racket);
}

void Ball::_collideWithBrick(Brick::Base* brick) {
    sf::FloatRect bounds = brick->getTrueBounds();
    if (!_collidesWithRect(bounds)) {
        return;
    }
    int sides = sideIntersect(bounds, getTrueBounds());
    if (sides & side::left) {
        _pos.x = bounds.left - (_pos.x - bounds.left);
        _speed.x = -_speed.x;
    }
    if (sides & side::top) {
        _pos.y = bounds.top - (_pos.y - bounds.top);
        _speed.y = -_speed.y;
    }
    if (sides & side::right) {
        _pos.x = bounds.left + bounds.width - (_pos.x - bounds.left - bounds.width);
        _speed.x = -_speed.x;
    }
    if (sides & side::bottom) {
        _pos.y = bounds.top + bounds.height - (_pos.y - bounds.top - bounds.height);
        _speed.y = -_speed.y;
    }
    setPosition(_pos);
}
void Ball::collideWith(Brick::Normal* brick) { _collideWithBrick(brick); }
void Ball::collideWith(Brick::Bonus* brick) { _collideWithBrick(brick); }
void Ball::collideWith(Brick::Invuln* brick) { _collideWithBrick(brick); }
void Ball::collideWith(Brick::Speed* brick) {
    sf::FloatRect bounds = brick->getTrueBounds();
    if (!_collidesWithRect(bounds)) {
        return;
    }
    // increasing speed means also increasing bounce distance
    float ratio = 1;
    if (normSq(_speed) < 15 * 15) {
        float speed = sqrt(normSq(_speed));
        ratio = std::min(speed + 2, 15.0f) / speed;
    }
    _speed *= ratio;
    int sides = sideIntersect(bounds, getTrueBounds());
    if (sides & side::left) {
        _pos.x = bounds.left - (_pos.x - bounds.left) * ratio;
        _speed.x = -_speed.x;
    }
    if (sides & side::top) {
        _pos.y = bounds.top - (_pos.y - bounds.top) * ratio;
        _speed.y = -_speed.y;
    }
    if (sides & side::right) {
        _pos.x = bounds.left + bounds.width - (_pos.x - bounds.left - bounds.width) * ratio;
        _speed.x = -_speed.x;
    }
    if (sides & side::bottom) {
        _pos.y = bounds.top + bounds.height - (_pos.y - bounds.top - bounds.height) * ratio;
        _speed.y = -_speed.y;
    }
    setPosition(_pos);
}
