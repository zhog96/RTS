#pragma once
#include "source/Scenes/Scene.hpp"

class MenuScene : public Scene {
private:
    typedef enum {BackGroundT, ButtonReleasedT, ButtonFocusedT} Textures;
    typedef enum {BackGroundS} Sprites;
    typedef enum {Font, Arial} Fonts;
    typedef enum {Exit, Play} Events;
public:
    MenuScene();
    int process();
    int draw();
};
