#include "game.hpp"
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    Game game(argc, argv);
    return game.run();
}
