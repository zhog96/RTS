#pragma once

#include <SFML/Graphics.hpp>
#include "Queue.hpp"

class Interface {
private:
    sf::RenderWindow window;
    void MainMenu(int button, sf::Texture & Background, sf::Texture & Button1, sf::Texture & Button2);
    Queue &q_Core_out;
    Queue &q_Core_in;

    sf::Font font;
public:
    Interface(Queue &q_Inter_out, Queue &q_Inter_in);
    int run();
};
