#pragma once

#include <TGUI/TGUI.hpp>

class MapObject {
protected:
    sf::Vector2f pos;
    sf::Vector2f size;
    sf::Vector2i drawId;
public:
    static sf::Vector2f mapPos;
    MapObject(sf::Vector2f pos);
    void solidMove(sf::Vector2f toPos);
    bool mouseOn();
    bool mouseClickedOn();
    virtual void update();
};