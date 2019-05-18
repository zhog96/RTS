#pragma once

#include <TGUI/TGUI.hpp>

class MapObject {
protected:
    sf::Vector2f pos;
    sf::Vector2i drawId;
public:
    MapObject(sf::Vector2f pos);
    void solidMove(sf::Vector2f toPos);
    bool mouseOn();
    bool mouseLeftClickedOn();
    bool mouseRightClickedOn();
    virtual void update();
};