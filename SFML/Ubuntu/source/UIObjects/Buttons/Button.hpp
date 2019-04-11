#pragma once
#include "source/UIObjects/UIObject.hpp"
#include "source/UIObjects/UIinformation.h"
#include "source/Tools/Time.h"

class Button : public UIObject {
protected:
public:
    Button(int id, std::vector<sf::Vector2i> &drawIds, sf::IntRect size);
    int process() override;
    virtual int motion();
};
