#include "Interface.hpp"

#include <stdio.h>
#include <string>
#include <SFML/System.hpp>

#include "source/UIObjects/UIinformation.h"
#include "source/Tools/Time.h"

sf::RenderWindow Interface::window;
Scene * Interface::scene = NULL;

int Interface::initInterface() {
    window.create(sf::VideoMode(1920, 1080), "SFML window");
    UIinformation::window = &window;
    scene = new MenuScene();
    //Check GPU, keyboard, ...
}

int Interface::run() {
    window.setFramerateLimit(60);

    Time::update();
    Time::update();
    while(window.isOpen()) {

        sf::Event event;
        sf::Mouse mouse;

        UIinformation::clicked = false;

        while(window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    UIinformation::clicked = true;
                }
            }
        }

        UIinformation::mPos = sf::Vector2<double>(mouse.getPosition(window));

        Time::update();
        scene->process();

        /*if(!q_Core_in.isEmpty()) {
            int k = q_Core_in.top();
            q_Core_in.pop();
            printf("%d\n", k);
        }*/

        scene->draw();
        
        window.display();
        window.clear();

        if(scene->getChange() == UIinformation::Scenes::Exit) {
            window.close();
        }
    }
}

