#include "game.hpp"
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    // asan returns 6240 bytes leaked from some calloc in window creation
    Game game(argc, argv);
    return game.run();
}
