#pragma once

#include <vector>
#include <queue>
#include "source/Tools/ICMessage.h"

class Tile {
public:
    int type;
    bool occupied;
    int occupierType;
    int occupierId;
};

class Unit {
public:
    int x, y;
    int HP;
    typedef enum {Idle, Moving, Attacking} states;
    int state;
    std::pair<int, int> destination;
};

class Building {
public:
    int x, y;
    int HP;
    typedef enum {Idle, Producing} states;
    int state;
    int destination;
};

class GameInformation {
public:
    static std::vector< std::vector< Tile > > playMap;
    static std::vector< Unit > units;
    static std::vector< Building > buildings;
    static std::queue< ICMessage > IntCoreQ;
    static std::queue< ICMessage > CoreIntQ;
};
