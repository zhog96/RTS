#include "Interface.hpp"

#include <stdio.h>
#include <string>

Interface::Interface(Queue &q_Core_out, Queue &q_Core_in) : q_Core_out(q_Core_out), q_Core_in(q_Core_in) {
    window.create(sf::VideoMode(1920, 1080), "SFML window");
    scene = new MenuScene(window);
    //Check GPU, keyboard, ...
}

int Interface::run() {

    while(window.isOpen()) {
        
        scene->process();

        if(!q_Core_in.isEmpty()) {
            int k = q_Core_in.top();
            q_Core_in.pop();
            printf("%d\n", k);
        }

        scene->draw();
        
        window.display();
        window.clear();
    }
}

