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
    static bool openTiles;
    static long long timeBoom;
    static sf::Vector2f openZeros;
    static std::vector<sf::Vector2f> positionBoom;

    static void loadMap(tgui::Canvas * canvas);
    static void update();
    static void clean();

    static void switchCase(sf::Vector2i task);
    static void updateObjects(sf::Vector2i task);

    static void checkTileStates(sf::Vector2i task);
    static void openAllTiles(sf::Vector2i task);
    static void win();
    static void lose();
};

