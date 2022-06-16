#include "field.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

Field::Field(std::string layoutFile, Game* parent) {
    _parent = parent;
    ifstream layoutStream(layoutFile);
}
