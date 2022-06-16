#ifndef FIELD_H_
#define FIELD_H_
#include "bonus.hpp"
#include "brick.hpp"
#include "declarations.hpp"
#include <memory>
#include <string>
#include <vector>

class Field {
  public:
    Field() = delete;
    Field(const std::string& layoutFile, sf::RenderWindow& window);
    int brickCollisions(Ball* ball);
    int bonusCollisions(Racket* racket);

    void draw();
    ~Field() = default;

  private:
    sf::RenderWindow& _window;
    std::vector<std::shared_ptr<Brick::Base>> bricks;
    std::vector<Bonus::Base*> bonuses;
};

#endif // FIELD_H_
