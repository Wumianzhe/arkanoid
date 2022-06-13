#ifndef BALL_H_
#define BALL_H_

#include "collision.hpp"
#include "entity.hpp"
#include <SFML/Graphics.hpp>

class Ball : public Entity, public sf::CircleShape, public collision::Actor {
  public:
    Ball() = delete;
    Ball(sf::Vector2f position, float radius);
    void move() override;
    void move(sf::Vector2f speed);
    void hitBy(Ball* ball) override{};
    void collideWith(Brick* brick) override;
    void collideWith(Bonus* bonus) override{};
    void collideWith(Racket* racket);
    void collideWithBorders(sf::RenderWindow* window) override;

    bool isOnRacket() { return onRacket; }
    void launch(Racket* racket);

  private:
    bool contains(sf::Vector2f point);
    bool onRacket = true;
};

#endif // BALL_H_
