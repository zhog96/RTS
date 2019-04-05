#pragma once
#include "source/Scenes/Scene.hpp"

class MenuScene : public Scene {
public:
    MenuScene(sf::RenderWindow &window);
    int process();
    int draw();
};
