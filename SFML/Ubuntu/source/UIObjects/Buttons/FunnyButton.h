#pragma once

#include "Button.hpp"

class FunnyButton : public Button {
private:
    double phi;
    sf::Transform startTr;
    sf::Transform startTextTr;
public:
    FunnyButton(int id, std::vector<sf::Texture *> &textures, sf::Transform trans, sf::Vector2<double> size, std::string text, sf::Transform textTrans, sf::Font *font);
    int motion() override;
};
