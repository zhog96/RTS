#pragma once

#include <SFML/Graphics.hpp>
#include "Queue.hpp"
#include "MenuScene.hpp"

class Interface {
private:
    sf::RenderWindow window;
    Queue &q_Core_out;
    Queue &q_Core_in;
    Scene * scene;
public:
    Interface(Queue &q_Inter_out, Queue &q_Inter_in);
    int run();
};
