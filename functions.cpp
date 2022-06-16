#include "functions.hpp"

float normSq(sf::Vector2f vec) { return vec.x * vec.x + vec.y * vec.y; }
int sideIntersect(sf::FloatRect one, sf::FloatRect other) {
    if (!one.intersects(other)) {
        return side::none;
    }

    bool overlapT = other.top > one.top - one.height;
    bool overlapB = other.top - other.height > one.top;
    bool overlapL = other.left - other.width > one.left;
    bool overlapR = other.left > one.left + one.width;

    return side::top * overlapT | side::bottom * overlapB | side::left * overlapL | side::right * overlapR;
}
