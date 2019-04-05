#pragma once

#include <SFML/Graphics.hpp>
#include "source/Tools/Queue.hpp"
#include "source/Scenes/MenuScene.hpp"

class Interface {
private:
    sf::RenderWindow window;
    Queue &q_Core_out;
    Queue &q_Core_in;
    MenuScene * scene;
public:
    Interface(Queue &q_Inter_out, Queue &q_Inter_in);
    int run();
};
