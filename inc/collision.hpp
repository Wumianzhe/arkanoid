#ifndef COLLISON_H_
#define COLLISON_H_

#include "bonus.hpp"
#include "brick.hpp"
#include <SFML/Graphics/RenderWindow.hpp>

namespace collision {
class Actor {
  public:
    Actor() = default;
    virtual void collideWith(Brick::Normal* brick) = 0;
    virtual void collideWith(Brick::Bonus* brick) = 0;
    virtual void collideWith(Brick::Invuln* brick) = 0;
    virtual void collideWith(Brick::Speed* brick) = 0;
    virtual void collideWith(Bonus::SpeedUp* bonus) = 0;
    virtual void collideWith(Bonus::SpeedDown* bonus) = 0;
    virtual void collideWith(Bonus::Shield* bonus) = 0;
    virtual void collideWith(Bonus::SizeUp* bonus) = 0;
    virtual void collideWith(Bonus::SizeDown* bonus) = 0;
    virtual void collideWith(Bonus::Sticky* bonus) = 0;
    virtual void collideWith(Bonus::Randomizer* bonus) = 0;
    virtual void collideWith(Bonus::BallUp* bonus) = 0;
    virtual void collideWithBorders(sf::RenderWindow* window) = 0;
    virtual ~Actor() = default;
};
} // namespace collision

#endif // COLLISON_H_
