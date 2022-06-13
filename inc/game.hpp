#ifndef GAME_H_
#define GAME_H_

#include "ball.hpp"
#include "racket.hpp"
#include <SFML/Graphics.hpp>

class Game {
  public:
    Game();
    int run();
    ~Game();

  private:
    void checkCollisions();

    sf::RenderWindow* window;
    sf::Font* font;

    int score;
    int lives;
    Racket* racket;
    Ball* ball;
};

#endif // GAME_H_
