#include "ball.hpp"
#include "racket.hpp"
#include <cmath>
#include <iostream>

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

float normSq(sf::Vector2f vec) { return vec.x * vec.x + vec.y * vec.y; }
bool Ball::contains(sf::Vector2f point) {
    float radius = getRadius();
    return normSq(point - _pos) <= radius * radius;
}

void Ball::collideWith(Brick* brick) { std::cout << "collision"; }
void Ball::collideWith(Racket* racket) {
    int boxIntersect = intersects(racket);
    sf::Vector2f racketSize = racket->getSize();
    sf::Vector2f racketPos = racket->getPosition();
    float radius = getRadius();
    float dt = 0;
    // if intersection is on one side, it will be fine, but corners need to be rechecked
    if (boxIntersect & side::left && boxIntersect & side::top) {
        // corner is outside circle
        if (!contains(racketPos)) {
            return;
        }
    }
    if (boxIntersect & side::right && boxIntersect & side::top) {
        // corner is outside circle
        if (!contains(racketPos + sf::Vector2f{racketSize.x, 0})) {
            return;
        }
    }
    // bottom collision is rare and quietly forgotten

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
}

void Ball::launch(Racket* racket) {
    onRacket = false;
    _pos.y += 1;
    collideWith(racket);
}
