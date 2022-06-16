#include "entity.hpp"
#include "functions.hpp"

using namespace sf;

int Entity::intersects(const Entity* other) const { return sideIntersect(getTrueBounds(), other->getTrueBounds()); }
