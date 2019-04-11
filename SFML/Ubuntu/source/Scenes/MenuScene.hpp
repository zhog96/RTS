#pragma once
#include "source/Scenes/Scene.hpp"

class MenuScene : public Scene {
private:
    typedef enum {BackGroundT, ButtonsT} Textures;
    typedef enum {Font, Arial} Fonts;
    typedef enum {Exit, Play} Events;
    sf::Vector2i BGid;
    sf::Vector2i HeadTextid;
public:
    MenuScene();
    int process();
    int draw();
};
