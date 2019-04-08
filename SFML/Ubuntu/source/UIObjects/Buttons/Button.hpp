#pragma once
#include "source/UIObjects/UIObject.hpp"
#include "source/UIObjects/UIinformation.h"
#include "source/Tools/Time.h"

class Button : public UIObject {
protected:
    sf::Text text;
    sf::Transform textTrans;
public:
    Button(int id, std::vector<sf::Texture *> &textures, sf::Transform trans, sf::Vector2<double> size, std::string text, sf::Transform textTrans, sf::Font *font);
    int process() override;
    int draw() override;
    virtual int motion();
};
