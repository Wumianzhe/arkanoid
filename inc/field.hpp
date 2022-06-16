#ifndef FIELD_H_
#define FIELD_H_
#include "brick.hpp"
#include "declarations.hpp"
#include <memory>
#include <string>
#include <vector>

// separated to make field cleanup/reload simpler (delete and recreate)
class Field {
    Field() = delete;
    Field(std::string layoutFile, Game* parent);
    void collisionTest(Ball* ball);
    ~Field();

  private:
    Game* _parent;
    std::vector<std::unique_ptr<Brick::Base>> bricks;
};

#endif // FIELD_H_
