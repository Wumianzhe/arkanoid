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
    void hitBy(Ball* ball) override;
    void hitBy(Racket* ball) override{};
    void collideWith(Brick::Normal* brick) override;
    void collideWith(Brick::Bonus* brick) override;
    void collideWith(Brick::Invuln* brick) override;
    void collideWith(Brick::Speed* brick) override;
    void collideWith(Bonus::SpeedUp* bonus) override {}
    void collideWith(Bonus::SpeedDown* bonus) override {}
    void collideWith(Bonus::Shield* bonus) override {}
    void collideWith(Bonus::SizeUp* bonus) override {}
    void collideWith(Bonus::SizeDown* bonus) override {}
    void collideWith(Bonus::Sticky* bonus) override {}
    void collideWith(Bonus::Randomizer* bonus) override {}
    void collideWith(Bonus::BallUp* bonus) override {}
    void collideWith(Racket* racket);
    void collideWithBorders(sf::RenderWindow* window) override;

    void adjustSpeed(float delta);
    void setRandomizer() { random_duration = 120; };

    bool isOnRacket() { return onRacket; }
    void launch(Racket* racket);

  private:
    void _collideWithBrick(Brick::Base* brick);
    bool _collidesWithRect(sf::FloatRect bounds) const;
    bool contains(sf::Vector2f point) const;
    bool onRacket = true;
    int random_duration = 0;
};

#endif // BALL_H_
