#pragma once

#include "Button.hpp"

class FunnyButton : public Button {
private:
    double phi;
public:
    FunnyButton(int id, std::vector<sf::Vector2i> *drawIds, std::vector<sf::Vector2i> *textIds);;
    int motion() override;
};
