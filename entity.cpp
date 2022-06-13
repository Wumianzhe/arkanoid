#include "entity.hpp"

using namespace sf;

int Entity::intersects(const Entity* other) const {
    Vector2f pos = other->_pos;
    FloatRect _bounds(_pos, {_bR.width, _bR.height});
    FloatRect bounds(pos, {other->_bR.width, other->_bR.height});

    if (!_bounds.intersects(bounds)) {
        return side::none;
    }

    bool overlapT = bounds.top > _bounds.top - _bounds.height;
    bool overlapB = bounds.top - bounds.height > _bounds.top;
    bool overlapL = bounds.left - bounds.width > _bounds.left;
    bool overlapR = bounds.left > _bounds.left + _bounds.width;

    return side::top * overlapT | side::bottom * overlapB | side::left * overlapL | side::right * overlapR;
}
