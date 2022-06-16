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
                    block = make_shared<Brick::Bonus>(pos, blockSize, 's');
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
        _window.draw(*brick);
    }
}

int Field::collisionTest(Ball* ball) {
    int scoreDelta = 0;
    for (auto brick : bricks) {
        if (brick->intersects(ball)) {
            brick->hitBy(ball);
            scoreDelta++;
            if (brick->isDead()) {
                brick = nullptr;
            }
        }
    }
    return scoreDelta;
}
