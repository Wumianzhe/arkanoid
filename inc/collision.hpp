#ifndef COLLISON_H_
#define COLLISON_H_

#include "brick.hpp"
#include "declarations.hpp"
#include <SFML/Graphics/RenderWindow.hpp>

namespace collision {
class Actor {
  public:
    Actor() = default;
    virtual void collideWith(Brick* brick) = 0;
    virtual void collideWith(Bonus* bonus) = 0;
    virtual void collideWithBorders(sf::RenderWindow* window) = 0;
    virtual ~Actor() = default;
};
} // namespace collision

#endif // COLLISON_H_
