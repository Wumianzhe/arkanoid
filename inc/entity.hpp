#ifndef ENTITY_H_
#define ENTITY_H_

#include <SFML/Graphics/Shape.hpp>
#include <declarations.hpp>

class Entity {
  public:
    Entity(sf::Vector2f pos, sf::Vector2f speed, sf::Vector2f size) : _pos(pos), _speed(speed), _bR({0, 0}, size){};
    enum side { none = 0, top = 1, bottom = 2, left = 4, right = 8 };

    virtual void move() = 0;
    virtual void hitBy(Ball* ball) = 0;
    void setSpeed(sf::Vector2f speed) { _speed = speed; };
    sf::Vector2f getSpeed() { return _speed; };

    // returns combination of flags corresponding to sides on which bounding rectangles of two entities intersect
    int intersects(const Entity* other) const;

  protected:
    sf::Vector2f _speed;
    sf::Vector2f _pos;
    sf::FloatRect _bR; // bounding rectangle
};

#endif // ENTITY_H_
