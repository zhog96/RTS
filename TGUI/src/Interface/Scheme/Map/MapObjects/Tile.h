#pragma once

#include "MapObject.h"

class Tile : public MapObject {
public:
    Tile(sf::Vector2f pos);
    void update() override;
};
