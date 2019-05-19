#pragma once

#include <TGUI/TGUI.hpp>
#include "MapInfo.h"

class MapObject {
public:
    sf::Vector2f pos;
    sf::Vector2i drawId;
    MapObject(sf::Vector2f pos);
    void solidMove(sf::Vector2f toPos);
    bool mouseOn();
    bool mouseLeftClickedOn();
    bool mouseRightClickedOn();
    virtual void update(int par = MapInfo::playStates::playing);
};