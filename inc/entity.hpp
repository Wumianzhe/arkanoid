#ifndef ENTITY_H_
#define ENTITY_H_

#include <SFML/Graphics/Shape.hpp>
#include <declarations.hpp>

// initially wanted to subclass sf::Entity, but too much rhomboid inheritance
class Entity {
  public:
    Entity(sf::Vector2f pos, sf::Vector2f speed, sf::Vector2f size) : _pos(pos), _speed(speed), _bR({0, 0}, size){};

    virtual void move() = 0;
    virtual void hitBy(Ball* ball) = 0;
    virtual void hitBy(Racket* racket) = 0;
    virtual ~Entity() = default;
    void setSpeed(sf::Vector2f speed) { _speed = speed; }
    sf::Vector2f getSpeed() const { return _speed; }
    sf::FloatRect getTrueBounds() const { return {_pos, {_bR.width, _bR.height}}; }

    // returns combination of flags corresponding to sides on which bounding rectangles of two entities intersect
    int intersects(const Entity* other) const;

  protected:
    sf::Vector2f _speed;
    sf::Vector2f _pos;
    sf::FloatRect _bR; // bounding rectangle
};

#endif // ENTITY_H_
