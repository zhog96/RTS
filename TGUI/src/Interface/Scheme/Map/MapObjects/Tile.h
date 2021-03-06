#pragma once

#include "MapObject.h"
#include "MapInfo.h"

class Tile : public MapObject {
public:
    typedef enum {DEFAULT, FLAGGED, QMARK, ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, BOMB, EMPTY, HIGHLIGHTED, BOMB_CROSSED, EXPLOSION} tileStates;
    Tile(sf::Vector2f pos, tileInfo * info);
    tileInfo * info;
    float phi;
    sf::Vector2f speed;
    void update(int par = MapInfo::playStates::playing) override;
    int state;
    int changeState(int newState);
   // void openZeros(int x, int y);
};
