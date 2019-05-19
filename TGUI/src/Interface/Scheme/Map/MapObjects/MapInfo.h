#pragma once

#include <vector>
#include <SFML/Audio.hpp>

struct tileInfo {
    int content;
    int state;
};

class MapInfo {
public:
    static sf::Vector2f mapPos;
    static bool mouseOnMap;
    static int pressedAfterPause[2];
    static sf::Vector2i mapSize;
    static int nBombs;
    typedef enum {bmb = 9} contents;
    typedef enum {def, flag, qmark, pressed, highlighted} states;
    static std::vector<std::vector<tileInfo>> tiles;
    static int flagsCnt;
    static int nClosedTiles;
    static int GenerateMap();
    static int OpenZeros(sf::Vector2i start);
    static int UpdateCounters();
};


