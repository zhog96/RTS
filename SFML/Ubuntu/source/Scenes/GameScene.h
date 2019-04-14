#pragma once
#include "source/Scenes/Scene.hpp"

class GameScene : public Scene {
private:
    typedef enum {BackGroundT, ButtonsT} Textures;
    typedef enum {Font, Arial} Fonts;
    typedef enum {Exit, Play} Events;
    sf::Vector2i BGid;
    sf::Vector2i HeadTextid;
public:
    GameScene();
    int process();
    int draw();
};
