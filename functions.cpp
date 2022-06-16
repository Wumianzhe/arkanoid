#include "functions.hpp"

float normSq(sf::Vector2f vec) { return vec.x * vec.x + vec.y * vec.y; }
// at which sides second intersects first
int sideIntersect(sf::FloatRect first, sf::FloatRect second) {
    sf::FloatRect cross;
    if (!first.intersects(second, cross)) {
        return side::none;
    }

    bool overlapT = cross.top == first.top;
    bool overlapB = cross.top + cross.height == first.top + first.height;
    bool overlapL = cross.left == first.left;
    bool overlapR = cross.left + cross.width == first.left + first.width;

    return side::top * overlapT | side::bottom * overlapB | side::left * overlapL | side::right * overlapR;
}
