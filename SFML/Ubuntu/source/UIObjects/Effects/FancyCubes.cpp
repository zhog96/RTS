#include "FancyCubes.h"
#include "../DrawArray.h"
#include "../UIinformation.h"

FancyCubes::FancyCubes(int id, std::vector<sf::Vector2i> *drawIds, sf::Vector2i blastPos, int count) : UIObject(id, drawIds) {
    sf::IntRect source = DrawArray::getSourceRect(this->drawIds[0]);
    sf::Vector2i size = DrawArray::getSize(this->drawIds[0]);
    for(int i = 0; i < count; i++) {
        cubesIds.emplace_back(DrawArray::addToLayer(this->drawIds[0].x,
            sf::IntRect(blastPos.x, blastPos.y, size.x, size.y), source));
        cubesSpeed.emplace_back(sf::Vector2f(1.0, 1.0));
    }
}

int FancyCubes::process() {
    for(int i = 0; i < cubesIds.size(); i++) {
        DrawArray::update(cubesIds[i], DrawArray::getPos(cubesIds[i]) + cubesSpeed[i]);
    }
}

//TODO destroy cubes after usage