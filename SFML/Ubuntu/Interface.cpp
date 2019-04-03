#include "Interface.hpp"

#include <stdio.h>
#include <string>

Interface::Interface(Queue &q_Core_out, Queue &q_Core_in) : q_Core_out(q_Core_out), q_Core_in(q_Core_in) {
    window.create(sf::VideoMode(1280, 720), "SFML window");
    //Check GPU, keyboard, ...
}

int Interface::run() {
    sf::Clock deltaClock;
    sf::Font font;
    std::string str = ":)";
    font.loadFromFile("font.ttf");

    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                window.close();
            }
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
            if(event.type == sf::Event::KeyPressed) {
                q_Core_out.push(event.key.code);
            }
        }

        if(!q_Core_in.isEmpty()) {
            int k = q_Core_in.top();
            q_Core_in.pop();
            str += " " + std::to_string(k + 1);
            printf("%d\n", k);
        }
        sf::CircleShape shape(100.f);
        shape.setFillColor(sf::Color::Red);
        window.draw(shape);
        sf::Text text(str, font, 50);
        window.draw(text);

        sf::Time dt = deltaClock.restart();
        window.display();
        window.clear();
    }
}
