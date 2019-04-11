#pragma once

#include "Button.hpp"

class FunnyButton : public Button {
private:
    double phi;
    sf::Vector2<double> pos;
public:
    FunnyButton(int id, std::vector<sf::Vector2i> &drawIds, sf::IntRect size);;
    int motion() override;
};
