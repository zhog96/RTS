#include "Interface.hpp"

#include <stdio.h>

Interface::Interface(Queue &q_Core_out, Queue &q_Core_in) : q_Core_out(q_Core_out), q_Core_in(q_Core_in) {
    window.create(sf::VideoMode(1920, 1080), "SFML window");
    //Check GPU, keyboard, ...
}

int Interface::run() {
    sf::Clock deltaClock;
    
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
            printf("%d\n", k);
        }

        sf::Time dt = deltaClock.restart();
        window.clear();
        window.display();
    }
}
