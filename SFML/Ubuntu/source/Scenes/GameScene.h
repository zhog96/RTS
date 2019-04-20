#pragma once
#include "source/Scenes/Scene.hpp"

class GameScene : public Scene {
private:
    typedef enum {BackGroundT, textureSheet} Textures;
    typedef enum {Font, Arial} Fonts;
    typedef enum {Exit, TilePressed} Events;
    sf::Vector2i BGid;
    sf::Vector2i HeadTextid;
    sf::Vector2i Panelid;
public:
    GameScene();
    int process();
    int draw();
};
