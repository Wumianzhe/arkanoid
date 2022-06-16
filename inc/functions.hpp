#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

float normSq(sf::Vector2f vec);
int sideIntersect(sf::FloatRect one, sf::FloatRect other);
enum side { none = 0, top = 1, bottom = 2, left = 4, right = 8 };

#endif // FUNCTIONS_H_
