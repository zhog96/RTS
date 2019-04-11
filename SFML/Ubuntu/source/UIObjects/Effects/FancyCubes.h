#pragma once

#include "../UIObject.hpp"

class FancyCubes : public UIObject {
protected:
    std::vector<sf::Vector2i> cubesIds;
    std::vector<sf::Vector2f> cubesSpeed;
public:
    FancyCubes(int id, std::vector<sf::Vector2i> *drawIds, sf::Vector2i blastPos, int count);
    int process() override;
};

