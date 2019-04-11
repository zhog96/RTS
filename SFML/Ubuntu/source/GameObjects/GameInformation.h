#pragma once

#include <vector>
#include <queue>
#include "source/Tools/ICMessage.h"

class Tile {
public:
    int type;
    bool occupied;
    int occupierId;
};

class Unit {
public:
    int x, y;
    int HP;
    int state;
    int destination;
};

class Building {
public:
    int x, y;
    int HP;
    int state;

};

class GameInformation {
public:
    static std::vector< std::vector< Tile > > playMap;
    static std::vector< Unit > units;
    static std::vector< Building > buildings;
    static std::queue<ICMessage> IntCoreQ;
};

