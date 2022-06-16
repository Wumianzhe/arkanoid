#ifndef BONUS_H_
#define BONUS_H_

#include "declarations.hpp"
#include "entity.hpp"
#include <SFML/Graphics.hpp>
#include <array>

namespace Bonus {
enum type {
    SPEED_UP = 0,
    SPEED_DOWN = 1,
    SHIELD = 2,
    SIZE_UP = 3,
    SIZE_DOWN = 4,
    STICKY = 5,
    RANDOMIZER = 6,
    BALL_UP = 7
};
static std::array<sf::Color, 8> color = {sf::Color(255, 0, 0), sf::Color(0, 0, 255),   sf::Color(255, 0, 255),
                                         sf::Color(0, 255, 0), sf::Color(128, 128, 0), sf::Color(0, 192, 0),
                                         sf::Color(192, 0, 0), sf::Color(0, 0, 192)};
class Base : public Entity, public sf::Shape {};
} // namespace Bonus

#endif // BONUS_H_
