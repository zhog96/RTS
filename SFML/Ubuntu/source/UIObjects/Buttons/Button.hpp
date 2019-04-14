#pragma once
#include "source/UIObjects/UIObject.hpp"
#include "source/UIObjects/UIinformation.h"
#include "source/Tools/Time.h"

class Button : public UIObject {
protected:
    sf::Vector2<double> pos;
    sf::Vector2<double> textpos;
public:
    Button(int id, std::vector<sf::Vector2i> *drawIds, std::vector<sf::Vector2i> *textIds = NULL);
    int process() override;
    virtual int motion();
};
