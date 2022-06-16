#include "game.hpp"

Game::Game(int argc, char** argv) {
    window = new sf::RenderWindow(sf::VideoMode(800, 600), "Arkanoid");
    font = new sf::Font;
    racket = new Racket({360, 580}, {80, 10});
    ball = new Ball({395, 570}, 5);

    // to be able to find local files when ran from other directory
    std::string dir = argv[0];
    dir = dir.substr(0, dir.find_last_of('/') + 1);

    if (!font->loadFromFile(dir + "overpass-light.ttf"))
        throw std::runtime_error("font loading failed");
    window->setVerticalSyncEnabled(true);
    // window->setFramerateLimit(10);
    window->setPosition({100, 100});
}

Game::~Game() {
    delete window;
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
        if (ball->isOnRacket()) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                ball->launch(racket);
            }
            ball->move(racket->getSpeed());
        } else {
            ball->move();
        }
        racket->move();
        checkCollisions();
        window->clear();
        window->draw(*racket);
        window->draw(*ball);
        window->display();
    }

    return 0;
}

void Game::checkCollisions() {
    if (ball->intersects(racket)) {
        ball->collideWith(racket);
    }
    // condition is inside already
    racket->collideWithBorders(window);
    ball->collideWithBorders(window);
}
