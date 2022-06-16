#ifndef GAME_H_
#define GAME_H_

#include "ball.hpp"
#include "field.hpp"
#include "racket.hpp"
#include <SFML/Graphics.hpp>

class Game {
  public:
    Game() = delete;
    Game(int argc, char** argv);

    int run();
    void draw();
    ~Game();
    Ball* getBall() const { return ball; }

  private:
    void checkCollisions();

    sf::RenderWindow* window;
    sf::Font* font;

    int score;
    int lives;
    Racket* racket;
    Ball* ball;
    Field* field;
};

#endif // GAME_H_
