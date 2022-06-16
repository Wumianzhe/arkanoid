#include "field.hpp"
#include "bonus.hpp"
#include "game.hpp"
#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

Field::Field(const std::string& layoutFile, sf::RenderWindow& window) : _window(window) {
    ifstream layoutStream(layoutFile);
    int height = 0, width = 0;
    int j = 0;
    sf::Vector2f blockSize;
    for (string line; getline(layoutStream, line);) {
        // skip comments
        if (line[0] == '#') {
            continue;
        }
        istringstream lineStream(line);
        if (!height && !width) {
            lineStream >> height >> width;
            blockSize = {float(window.getSize().x) / width, float(window.getSize().y - 200) / height};
        } else {
            for (int i = 0; i < width; i++) {
                char inType;
                std::shared_ptr<Brick::Base> block = nullptr;
                sf::Vector2f pos = {blockSize.x * i, blockSize.y * j};

                lineStream >> inType;
                if (inType > '0' && inType <= '5') {
                    block = make_shared<Brick::Normal>(pos, blockSize, int(inType - '0'));
                }
                switch (inType) {
                case 'i': {
                    block = make_shared<Brick::Invuln>(pos, blockSize);
                    break;
                }
                case 'a': {
                    block = make_shared<Brick::Speed>(pos, blockSize);
                    break;
                }
                case 's': {
                    block = make_shared<Brick::Bonus>(pos, blockSize, Bonus::type::SIZE_DOWN);
                    break;
                }
                case 'w': {
                    block = make_shared<Brick::Bonus>(pos, blockSize, Bonus::type::SIZE_UP);
                    break;
                }
                case 'u': {
                    block = make_shared<Brick::Bonus>(pos, blockSize, Bonus::type::SPEED_UP);
                    break;
                }
                case 'd': {
                    block = make_shared<Brick::Bonus>(pos, blockSize, Bonus::type::SPEED_DOWN);
                    break;
                }
                case 't': {
                    block = make_shared<Brick::Bonus>(pos, blockSize, Bonus::type::STICKY);
                    break;
                }
                case 'h': {
                    block = make_shared<Brick::Bonus>(pos, blockSize, Bonus::type::SHIELD);
                    break;
                }
                case 'b': {
                    block = make_shared<Brick::Bonus>(pos, blockSize, Bonus::type::BALL_UP);
                    break;
                }
                default: {
                    break;
                }
                }
                if (block) {
                    bricks.push_back(block);
                }
            }
            j++;
        }
    }
}

void Field::draw() {
    for (auto brick : bricks) {
        if (brick) {
            _window.draw(*brick);
        }
    }
}

int Field::brickCollisions(Ball* ball) {
    int scoreDelta = 0;
    for (auto& brick : bricks) {
        if (brick->intersects(ball)) {
            brick->hitBy(ball);
            scoreDelta++;
            if (brick->isDead()) {
                if (brick->hasBonus()) {
                    Bonus::Base* bonus = nullptr;
                    auto bounds = brick->getTrueBounds();
                    sf::Vector2f center = {bounds.left + bounds.width, bounds.top + bounds.height};
                    switch (brick->getBonusType()) {
                    case Bonus::SPEED_UP: {
                        bonus = new Bonus::SpeedUp(center);
                    }
                    case Bonus::SPEED_DOWN: {
                        bonus = new Bonus::SpeedDown(center);
                    }
                    case Bonus::SHIELD: {
                        bonus = new Bonus::Shield(center);
                    }
                    case Bonus::SIZE_UP: {
                        bonus = new Bonus::SpeedDown(center);
                    }
                    case Bonus::SIZE_DOWN: {
                        bonus = new Bonus::SpeedDown(center);
                    }
                    case Bonus::STICKY: {
                        bonus = new Bonus::SpeedDown(center);
                    }
                    case Bonus::RANDOMIZER: {
                        bonus = new Bonus::SpeedDown(center);
                    }
                    case Bonus::BALL_UP: {
                        bonus = new Bonus::SpeedDown(center);
                    }
                        bonuses.push_back(bonus);
                    }
                }
                brick = nullptr;
            }
        }
    }
    return scoreDelta;
}

int Field::bonusCollisions(Racket* racket) {
    for (auto& bonus : bonuses) {
        if (racket->intersects(bonus)) {
            bonus->hitBy(racket);
        }
    }
}
