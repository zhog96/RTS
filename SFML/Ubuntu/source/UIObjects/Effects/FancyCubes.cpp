#include "FancyCubes.h"
#include "../DrawArray.h"
#include "../UIinformation.h"
#include "source/Tools/Time.h"
#include <math.h>

FancyCubes::FancyCubes(int id, std::vector<sf::Vector2i> *drawIds, sf::Vector2i blastPos, int count) : UIObject(id, drawIds) {
    sf::IntRect source = DrawArray::getSourceRect(this->drawIds[0]);
    sf::Vector2i size = DrawArray::getSize(this->drawIds[0]);
    for(int i = 0; i < count; i++) {
        cubesIds.emplace_back(DrawArray::addToLayer(id,
            sf::IntRect(blastPos.x, blastPos.y, size.x, size.y), source));
        cubesSpeed.emplace_back(sf::Vector2f(0.1 * sin(rand()), 0.1 * cos(rand())));
    }
    creatTime = Time::time;
}

int FancyCubes::process() {
    for(int i = 0; i < cubesIds.size(); i++) {
        DrawArray::update(cubesIds[i], DrawArray::getPos(cubesIds[i]) + Time::delta / 1000.f * cubesSpeed[i]);
        cubesSpeed[i] += 0.3f * (Time::delta / 1000000.f) * sf::Vector2f(0.f, 1.f);
    }
    if(Time::time - creatTime > 10 * 1000000) {
        for(int i = 0; i < drawIds.size(); i++) DrawArray::erase(drawIds[i]);
        drawIds.clear();
        for(int i = 0; i < cubesIds.size(); i++) DrawArray::erase(cubesIds[i]);
        cubesIds.clear();
        forDelete = true;
    }
}