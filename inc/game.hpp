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
    void setBarrier() { _hasBarrier = true; }
    void speedCallback(float delta);
    void randomizerCallback();
    void ballUpCallback(sf::Vector2f pos);

  private:
    void checkCollisions();
    void bottomCollision(Ball* ball);

    sf::RenderWindow* window;
    sf::Font* font;

    int score;
    int lives;
    Racket* racket;
    std::vector<Ball*> balls;
    Field* field;
    bool _hasBarrier = false;
};

#endif // GAME_H_
