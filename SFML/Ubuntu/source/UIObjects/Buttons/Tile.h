#pragma once

#include "Button.hpp"

class Tile : public Button {
private:
    double phi;
public:
    Tile(int id, std::vector<sf::Vector2i> *drawIds, std::vector<sf::Vector2i> *textIds);;
    int motion() override;
};
