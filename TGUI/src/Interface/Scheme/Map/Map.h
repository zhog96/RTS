#pragma once

#include <TGUI/TGUI.hpp>
#include <vector>

#include "MapObjects/MapObjects.h"

class Map {
private:
    static std::vector<MapObject *> objects;
public:
    static sf::Texture tiles;
    static tgui::Canvas * canvas;
    static sf::Vector2f camera;
    static float height;
    static long long timeBoom;
    static std::vector<sf::Vector2f> positionBoom;

    static void loadMap(tgui::Canvas * canvas);
    static void update();
    static void clean();

    static void checkTileStates();
    static void openAllTiles();
    static void win();
    static void lose();
};

