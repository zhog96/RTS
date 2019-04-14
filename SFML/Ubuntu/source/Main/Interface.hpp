#pragma once

#include <SFML/Graphics.hpp>
#include "source/Tools/Queue.hpp"
#include "source/Scenes/MenuScene.hpp"
#include "source/Scenes/Scene.hpp"

class Interface {
public:

    static sf::RenderWindow window;
    static Scene * scene;

    static int initInterface();
    static int run();
};
