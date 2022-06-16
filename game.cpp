#include "game.hpp"

Game::Game(int argc, char** argv) {
    window = new sf::RenderWindow(sf::VideoMode(800, 600), "Arkanoid");
    font = new sf::Font;
    racket = new Racket({360, 580}, {80, 10}, *this);
    balls.push_back(new Ball({395, 570}, 5));

    // to be able to find local files when ran from other directory
    std::string dir = argv[0];
    dir = dir.substr(0, dir.find_last_of('/') + 1);

    if (!font->loadFromFile(dir + "overpass-light.ttf"))
        throw std::runtime_error("font loading failed");
    field = new Field(dir + "layout.cfg", *window);
    window->setVerticalSyncEnabled(true);
    // window->setFramerateLimit(15);
    window->setPosition({100, 100});
}

Game::~Game() {
    delete window;
    delete racket;
    delete field;
    delete font;
}

int Game::run() {
    while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                window->close();
                break;
            case sf::Event::KeyPressed: {
                if (event.key.code == sf::Keyboard::Escape) {
                    window->close();
                    break;
                }
            }
            case sf::Event::Resized:
                break;
            default:
                break;
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            racket->accelLeft();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            racket->accelRight();
        }
        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            racket->stopAccel();
        }
        for (auto ball : balls) {
            if (ball->isOnRacket()) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                    ball->launch(racket);
                }
                ball->move(racket->getSpeed());
            } else {
                ball->move();
            }
        }
        racket->move();
        checkCollisions();
        window->clear();
        draw();
        window->display();
    }

    return 0;
}
void Game::draw() {
    field->draw();
    window->draw(*racket);
    for (auto ball : balls) {
        window->draw(*ball);
    }
}

void Game::checkCollisions() {
    for (auto ball : balls) {
        if (racket->intersects(ball)) {
            racket->hitBy(ball);
        }
        score += field->brickCollisions(ball);

        ball->collideWithBorders(window);
    }

    racket->collideWithBorders(window);
}

void Game::bottomCollision(Ball* ball) {
    if (ball->getPosition().y + 2 * ball->getRadius() > window->getSize().y) {
        score--;
    }
}

void Game::speedCallback(float delta) {
    for (auto ball : balls) {
        ball->adjustSpeed(delta);
    }
}
void Game::randomizerCallback() {
    for (auto ball : balls) {
        ball->setRandomizer();
    }
}
void Game::ballUpCallback(sf::Vector2f pos) {
    if (balls.size() < 3) {
        Ball* ball = new Ball(pos, 5);
        balls.push_back(ball);
    }
}
